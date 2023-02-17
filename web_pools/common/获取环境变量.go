package main

import (
    "fmt"
    "os"
    "strings"
)

func main() {
    os.Setenv("name", "jacky")
    os.Setenv("id", "12345")
    fmt.Println("name:", os.Getenv("name"))
    fmt.Println("id:", os.Getenv("id"))
    for _, e := range os.Environ() {
        pair := strings.SplitN(e, "=", 2)
        fmt.Println(pair[0])
    }
}
