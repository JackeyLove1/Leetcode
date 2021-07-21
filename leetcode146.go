import "container/list"

type entry struct {
	k, v int
}

type LRUCache struct {
	ll       *list.List
	cache    map[int]*list.Element
	capacity int
}

func Constructor(capacity int) LRUCache {
	return LRUCache{
		ll:       list.New(),
		cache:    make(map[int]*list.Element),
		capacity: capacity,
	}
}

func (this *LRUCache) Get(key int) int {
	if ele, ok := this.cache[key]; ok {
		kv := ele.Value.(*entry)
		this.ll.MoveToFront(ele)
		return kv.v
	} else {
		return -1
	}
}

func (this *LRUCache) Put(key int, value int) {
	if ele, ok := this.cache[key]; ok {
		kv := ele.Value.(*entry)
		kv.v = value
		this.ll.MoveToFront(ele)
	} else {
		ele := this.ll.PushFront(&entry{key, value})
		this.cache[key] = ele
		if this.ll.Len() > this.capacity {
			old := this.ll.Back()
			this.ll.Remove(old)
			delete(this.cache, old.Value.(*entry).k)
		}
	}
}
