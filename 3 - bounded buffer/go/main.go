package main

import "fmt"
import "time"

func producer(buf chan<- int) {
	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		// TODO: push real value to buffer
		buf <- i
	}

}

func consumer(buf <-chan int) {
	time.Sleep(1 * time.Second)
	for {
		i := <-buf
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}

}

func main() {
	// TODO: make a bounded buffer
	var buf = make(chan int, 5)

	go consumer(buf)
	go producer(buf)

	select {}
}
