package main

import "fmt"

func MapKeys[K comparable, V any](m map[K]V) []K {
    r := make([]K, 0, len(m))
    for k := range m {
        r = append(r, k)
    }
    return r
}

func main() {
    m := map[int]string{1: "2", 2: "3", 3: "4"}
    keys := MapKeys(m)
    // println(keys)
    fmt.Println(keys)
}
