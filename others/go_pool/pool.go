package go_pool

import (
	"sync"
	"sync/atomic"
)

type Pool struct {
	// 容量 -1 负数代表无限
	capacity int32

	// 当前正在运行的worker数目
	running int32

	// 锁
	lock sync.Locker

	// 闲置worker
	freeWorkers workerContainer

	// 回收池
	workerCache sync.Pool

	// 当前状态 0stop 1run
	state int32

	// 条件变量
	cond *sync.Cond

	// 运行的函数
	poolFunc func(interface{})
}

func NewPool(cap int32) (*Pool, error) {
	if cap == 0 {
		return nil, ErrInvalidCapacity
	}

	pool := &Pool{}

	pool.lock = new(sync.Mutex)
	pool.state = 1
	pool.capacity = cap
	pool.running = 0
	pool.workerCache.New = func() interface{} {
		return &goWorker{
			pool:  pool,
			tasks: make(chan func(), DefaultWorkerChanSize),
		}
	}
	pool.cond = sync.NewCond(pool.lock)
	pool.freeWorkers = NewWorkArray()
	pool.poolFunc = nil

	return pool, nil
}

func NewPoolWithFunc(cap int32, pFunc func(interface{})) (*Pool, error) {
	if cap == 0 {
		return nil, ErrInvalidCapacity
	}

	pool := &Pool{}

	pool.lock = new(sync.Mutex)
	pool.state = 1
	pool.capacity = cap
	pool.running = 0
	pool.workerCache.New = func() interface{} {
		return &goWorker{
			pool:  pool,
			tasks: make(chan func(), DefaultWorkerChanSize),
		}
	}
	pool.cond = sync.NewCond(pool.lock)
	pool.freeWorkers = NewWorkArray()
	pool.poolFunc = pFunc


	return pool, nil
}

func (p *Pool) Close() {
	atomic.CompareAndSwapInt32(&p.state, p.state, 0)
	go p.freeWorkers.reset()
}

func (p *Pool) IsClosed() bool {
	return atomic.LoadInt32(&p.state) == 0
}

func (p *Pool) Submit(task func()) error {
	if p.IsClosed() {
		return ErrPoolClosed
	}

	var gw *goWorker
	var err error

	if gw, err = p.getWorker(); err != nil {
		return err
	}
	if gw == nil {
		return ErrInvalidWorker
	}

	gw.tasks <- task
	gw.run()

	return nil
}

func (p *Pool) getWorker() (*goWorker, error) {
	if p.IsClosed() {
		return nil, ErrPoolClosed
	}
	// 上锁
	// 先从freeWorker中寻找
	// 如果没有，检查是否可以生成新goWorker
	// capacity > running 或者 capacity < 0
	// 生成新worker使用Sync.Pool Get的方式获取
	// 不满足上述条件，就应该等待条件变量

	p.lock.Lock()
	// 使用cond时不能使用defer unlock
	// defer p.lock.Unlock()

	gw := p.freeWorkers.pop()
	if gw != nil {
		p.lock.Unlock()
		return gw, nil
	}

	spawnWorker := func() *goWorker {
		gw := p.workerCache.Get().(*goWorker)
		return gw
	}

	if p.Running() < p.capacity || p.capacity < 0 {
		gw = spawnWorker()
		p.lock.Unlock()
		return gw, nil
	}

	p.cond.Wait()
	// 再尝试一次
	gw = p.freeWorkers.pop()
	if gw != nil {
		p.lock.Unlock()
		return gw, nil
	}
	// 否则直接从Sync.Pool中获取
	gw = spawnWorker()
	p.lock.Unlock()
	return gw, nil
}

func (p *Pool) Running() int32 {
	return atomic.LoadInt32(&p.running)
}

func (p *Pool) IncRunning() {
	atomic.AddInt32(&p.running, 1)
}

func (p *Pool) DecRunning() {
	atomic.AddInt32(&p.running, -1)
}
