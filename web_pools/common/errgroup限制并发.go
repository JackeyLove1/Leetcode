package main

import (
    "context"
    "fmt"
    "runtime"
    "sync/atomic"
    "time"

    "github.com/go-resty/resty/v2"
    "golang.org/x/sync/errgroup"
)

func work(index int, ch chan bool) {
    println(time.Now().Local().String(), " index:", index, ", goroutine cnt:", runtime.NumGoroutine())
    time.Sleep(30 * time.Millisecond)
    <-ch // release
}

func main() {
    ctx := context.Background()
    g, ctx := errgroup.WithContext(ctx)
    g.SetLimit(10)
    client := resty.New()
    var ops uint64 = 0
    for i := 0; i < 10; i++ {
        g.Go(func() error {
            _, err := client.R().EnableTrace().Get("www.baidu.com")
            time.Sleep(300 * time.Millisecond)
            atomic.AddUint64(&ops, 1)
            fmt.Println("ops: ", atomic.LoadUint64(&ops))
            return err
        })
    }
    if err := g.Wait(); err == nil {
        fmt.Println("Success!")
    }
    maxTask := 1000
    ch := make(chan bool, 10)
    for i := 0; i < maxTask; i++ {
        ch <- true // block
        go work(i, ch)
    }
    time.Sleep(100 * time.Millisecond)
    close(ch)
}
