/*
基于ZooKeeper的锁与基于Redis的锁的不同之处在于Lock成功之前会一直阻塞，这与我们单机场景中的mutex.Lock很相似。

其原理也是基于临时Sequence节点和watch API，例如我们这里使用的是/lock节点。Lock会在该节点下的节点列表中插入自己的值，只要节点下的子节点发生变化，就会通知所有watch该节点的程序。这时候程序会检查当前节点下最小的子节点的id是否与自己的一致。如果一致，说明加锁成功了。

这种分布式的阻塞锁比较适合分布式任务调度场景，但不适合高频次持锁时间短的抢锁场景。按照Google的Chubby论文里的阐述，基于强一致协议的锁适用于粗粒度的加锁操作。这里的粗粒度指锁占用时间较长。我们在使用时也应思考在自己的业务场景中使用是否合适。
*/
package main

import (
    "time"

    "github.com/samuel/go-zookeeper/zk"
)

func main() {
    c, _, err := zk.Connect([]string{"127.0.0.1"}, time.Second) //*10)
    if err != nil {
        panic(err)
    }
    l := zk.NewLock(c, "/lock", zk.WorldACL(zk.PermAll))
    err = l.Lock()
    if err != nil {
        panic(err)
    }
    println("lock succ, do your business logic")

    time.Sleep(time.Second * 10)

    // do some thing
    l.Unlock()
    println("unlock succ, finish business logic")
}