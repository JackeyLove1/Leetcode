package main

import (
    "fmt"
    "os"
    "os/signal"
    "syscall"
)

func main() {
    signs := make(chan os.Signal, 1)

    signal.Notify(signs, syscall.SIGINT, syscall.SIGTERM)

    done := make(chan bool, 1)

    go func() {
        sig := <-signs
        println()
        fmt.Println(sig)
        done <- true
    }()

    fmt.Println("awaiting signal")
    <-done
    fmt.Println("exiting")
}
