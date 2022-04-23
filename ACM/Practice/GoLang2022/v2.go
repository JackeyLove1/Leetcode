package main

import (
	"fmt"
	"time"
)

func worker1(done chan bool) {
	fmt.Println("Start Working ... ")
	time.Sleep(time.Second)
	fmt.Println("Done ... ")
	done <- true
}

func worker(id int, jobs <-chan int, results chan<- int) {
	for job := range jobs {
		fmt.Println("Worker", id, " Start...")
		time.Sleep(time.Second)
		fmt.Println("Woker", id, " Done...")
		results <- job * job
	}
}

func main() {
	c1 := make(chan string)
	c2 := make(chan string)

	go func(c chan string) {
		// time.Sleep(time.Second)
		c <- "Hello"
	}(c1)

	go func(c chan string) {
		// time.Sleep(time.Second)
		c <- "World"
	}(c2)

	for i := 0; i < 3; i++ {
		select {
		case msg := <-c1:
			println("c1:", msg)
		case msg := <-c2:
			println("c2:", msg)
		default:
			println("Ending ... ")
		}
	}

	//
	timer1 := time.NewTimer(time.Second)
	<-timer1.C
	fmt.Println("Clicking ... ")

	const numJobs = 5
	const numWorkers = 3
	const numbers = 10

	jobs := make(chan int, numJobs)
	results := make(chan int, numJobs)

	for i := 0; i < numWorkers; i++ {
		go worker(i, jobs, results)
	}

	for i := 0; i < numbers; i++ {
		jobs <- i
	}

	close(jobs)

	for i := 0; i < numbers; i++ {
		result := <-results
		println("result: ", result)
	}
	close(results)

}
