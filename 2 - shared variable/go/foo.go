// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	"runtime"
)

func numberServer(add <-chan int, sub <-chan int, read chan<- int) {
	var number = 0

	// This for-select pattern is one you will become familiar with...
	for {
		select {
		case i := <-add:
			number += i
		case i := <-sub:
			number -= i
		case read<- number:
			continue
		}
	}
}

func incrementer(add chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000; j++ {
		add <- 1
	}
	fmt.Println("Done with inc")
	finished <- true
}

func decrementer(sub chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000+1; j++ {
		sub <- 1
	}
	fmt.Println("Done with dec")
	finished <- true
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	add := make(chan int)
	sub := make(chan int)
	read := make(chan int)

	finished := make(chan bool)

	// TODO: Spawn the required goroutines
	go incrementer(add, finished)
	go decrementer(sub, finished)

	go numberServer(add, sub, read)

	for _ = range []int{1, 2} {
		<-finished
	}

	fmt.Println("The magic number is:", <-read)
}
