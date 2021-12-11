package go_pool

const(
	DefaultItemSize = 10
)

// 放置worker的容器
// 并发时需要先加锁
type workerContainer interface {
	// 获得目前的worker数目
	size() int

	// 是否为空
	isEmpty() bool

	// 插入一个worker
	push(worker *goWorker) error

	// 取出一个worker
	pop() *goWorker

	// 重置
	reset()
}

// 使用简单的数组实现
type workerArray struct {
	items []*goWorker
}

func NewWorkArray() *workerArray{
	return &workerArray{
		items: make([]*goWorker, DefaultItemSize),
	}
}

func (w *workerArray) size() int {
	return len(w.items)
}

func (w *workerArray) isEmpty() bool {
	return len(w.items) == 0
}

func (w *workerArray) push(worker *goWorker) error {
	w.items = append(w.items, worker)
	return nil
}

func (w *workerArray) pop() *goWorker {
	if w.isEmpty() {
		return nil
	}
	popWorker := w.items[0]
	w.items[0] = nil // 方便gc
	w.items = w.items[1:]
	return popWorker
}

func (w *workerArray) reset() {
	// 向任务队列发送nil，表示中止协程
	//为了复用底部的内存，而非直接置nil

	for i := 0; i < len(w.items); i++{
		w.items[i].tasks <- nil
	}

	w.items = w.items[:0]
}
