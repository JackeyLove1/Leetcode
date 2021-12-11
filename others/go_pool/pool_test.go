package go_pool

import (
	"fmt"
	"sync"
	"testing"
	"time"
)

func TestNewPool(t *testing.T) {
	p, err := NewPool(10)
	if err != nil {
		t.Log(err.Error())
	}
	if p == nil {
		t.Log("p is nil")
	}
	if p.capacity != 10 {
		t.Log("p.capacity is error !")
	}
	if p.Running() != 0 {
		t.Log("p's running nums is error !")
	}
}

func TestGetPoolWorker(t *testing.T) {
	N := 10
	p, err := NewPool(int32(N))
	if err != nil {
		t.Fatal(err.Error())
	}
	var wg sync.WaitGroup
	for i := 0; i < N/2; i++ {
		wg.Add(1)
		go func(wg *sync.WaitGroup, p *Pool) {
			defer wg.Done()
			worker, err := p.getWorker()
			if err != nil {
				t.Errorf("get worker error: %s\n", err.Error())
			}
			if worker == nil {
				t.Error("get the nil worker!")
			}

		}(&wg, p)
	}
	wg.Wait()
}

func TestGetPoolMoreThread(t *testing.T) {
	N := 20
	p, err := NewPool(int32(N))
	if err != nil {
		t.Fatal(err.Error())
	}
	var wg sync.WaitGroup
	for i := 0; i < N*2; i++ {
		wg.Add(1)
		go func(wg *sync.WaitGroup, p *Pool) {
			defer wg.Done()
			worker, err := p.getWorker()
			if err != nil {
				t.Errorf("get worker error: %s\n", err.Error())
			}
			if worker == nil {
				t.Error("get the nil worker!")
			}

		}(&wg, p)
	}
	wg.Wait()
}

func TestNewPoolWithFunc1(t *testing.T) {
	N := 10
	p, err := NewPool(int32(N))
	if err != nil {
		t.Fatal(err.Error())
	}
	var wg sync.WaitGroup
	f := func(index int) {
		fmt.Printf("%d hello, world!\n", index)
	}
	for i := 0; i < N/2; i++ {
		wg.Add(1)
		go func(wg *sync.WaitGroup, p *Pool, index int) {
			defer wg.Done()
			err := p.Submit(func() {
				f(index)
			})
			if err != nil {
				t.Log(err.Error())
			}

		}(&wg, p, i)
	}
	wg.Wait()
	// time.Sleep(2)
}

func TestNewPoolWithFunc2(t *testing.T) {
	N := 5
	p, err := NewPool(int32(N))
	if err != nil {
		t.Fatal(err.Error())
	}
	var wg sync.WaitGroup
	f := func(index int) {
		fmt.Printf("%d hello, world!\n", index)
	}
	for i := 0; i < N*2; i++ {
		wg.Add(1)
		go func(wg *sync.WaitGroup, p *Pool, index int) {
			defer wg.Done()
			err := p.Submit(func() {
				f(index)
			})
			if err != nil {
				t.Log(err.Error())
			}

		}(&wg, p, i)
	}
	wg.Wait()
	// time.Sleep(2)
}

func TestNewPoolWithFunc3(t *testing.T) {

}

const (
	BenchSize = 200000
	RunTimes  = 100000
	SleepTime = 5 * time.Microsecond
	Loop = 10
)

func sleepFunc() {
	time.Sleep(SleepTime)
}

func TestNewPoolMore(t *testing.T) {
	p, err := NewPool(int32(1))

	if err != nil {
		t.Fatal(err.Error())
	}
	defer p.Close()

	for i := 0; i < Loop; i++ {
		for j := 0; j < RunTimes; j++ {
			err := p.Submit(sleepFunc)
			if err != nil{
				t.Fatal(err.Error())
			}
		}
	}
}

func BenchmarkNewPool(b *testing.B) {
	// 	测试结果2.68 * 10 ^ 8
	// 相较于下面的方法提升了10倍速度
	p, err := NewPool(int32(BenchSize))

	if err != nil {
		b.Fatal(err.Error())
	}
	defer p.Close()

	for i := 0; i < b.N; i++ {
		for j := 0; j < RunTimes; j++ {
			err := p.Submit(sleepFunc)
			if err != nil{
				b.Fatal(err.Error())
			}
		}
	}
}

func BenchmarkCommonGet(b *testing.B) {
	// 测试结果2.7 * 10 ^ 7
	var wg sync.WaitGroup
	for i := 0; i < b.N; i++ {
		for j := 0; j < RunTimes; j++ {
			wg.Add(1)
			go func(wg *sync.WaitGroup) {
				wg.Done()
				sleepFunc()
			}(&wg)
		}
	}
	wg.Wait()
}