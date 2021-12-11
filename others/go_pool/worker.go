package go_pool

const (
	DefaultWorkerChanSize = 1
)

type goWorker struct {
	// 指向协程池
	pool *Pool

	// 任务队列
	tasks chan func()

	// 函数参数列表
	args chan interface{}
}

func (gw *goWorker) run() {
	go func() {
		gw.pool.IncRunning()
		defer func() {
			gw.pool.DecRunning()
			// 回收gw
			gw.pool.workerCache.Put(gw)
		}()

		if gw.pool.IsClosed() {
			return
		}

		// 从任务队列中取出任务
		for f := range gw.tasks{
			if f == nil{
				return
			}
			f()
			// 放回freeWorkers
			// 唤醒cond
			if err := gw.returnWorker(); err != nil{
				return
			}
			gw.pool.cond.Signal()
		}
	}()
}

// 归还worker函数，需要上锁
func (gw *goWorker) returnWorker() error{
	gw.pool.lock.Lock()
	defer gw.pool.lock.Unlock()

	err := gw.pool.freeWorkers.push(gw)
	if err != nil{
		return err
	}
	return nil
}