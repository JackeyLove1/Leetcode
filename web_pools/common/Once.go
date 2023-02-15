package main

import (
    "log"
    "os"
    "sync"
    "time"
)

type Config struct {
    Server string
    Port   int64
}

var (
    once   sync.Once
    config *Config
)

func ReadConfig() *Config {
    once.Do(func() {
        config = &Config{
            Server: os.Getenv("TT_SERVER_URL"),
            Port:   time.Now().UnixNano()}
        log.Println("init config")
    })
    return config
}

func main() {
    var wg sync.WaitGroup
    tmp := ReadConfig().Port
    for i := 0; i < 10; i++ {
        wg.Add(1)
        go func(group *sync.WaitGroup) {
            defer group.Done()
            cfg := ReadConfig()
            if cfg.Port != tmp {
                log.Println("Error")
            }
        }(&wg)
    }
    wg.Wait()
    // time.Sleep(time.Second)
}
