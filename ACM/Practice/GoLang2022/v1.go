package main

import (
	"fmt"
	"time"
)

func val() (int, int) {
	return 1, 2
}

func sum(nums ...int) int {
	total := 0
	for _, num := range nums {
		total += num
	}
	return total
}

type Person struct {
	name string
	age int
}

func coroutine(){
	for i := 0; i < 3; i++{
		fmt.Println(i)
		time.Sleep(time.Millisecond * 100)
	}
}

func main() {
	fmt.Println("Hello, World!")
	m := make(map[int]string)

	m[1] = "one"
	m[2] = "two"
	fmt.Println(m)

	if _, flag := m[3]; !flag {
		fmt.Println("No exists 3")
	}

	a, b := val()
	fmt.Println("a: ", a, " b: ", b)

	s := sum(1, 2, 3)
	fmt.Println("s:", s)

	p := Person{name: "fhj", age: 100}
	fmt.Println(p)


	for i := 0; i < 3; i++{
		go coroutine()
	}

	time.Sleep(time.Second)

}
