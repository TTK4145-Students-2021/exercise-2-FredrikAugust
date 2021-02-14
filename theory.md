Exercise 2 - Theory questions
-----------------------------

### What is an atomic operation?
> An atomic operation is an operation that is performed isolated from all "side effects". An atomic operation cannot be disturbed by other processes or threads.

### What is a critical section?
> A critical section is the memory that several threads/processes will work on; we often organise work with this memory with mutexes and/or semaphores to ensure that only one thread/process modifies the memory at once.

### What is the difference between race conditions and data races?
> In a race condition the outcome is a result of the operations of several threads being intertwined. A data race happens when more than one thread attempts to modify a section of data at once.

### What are the differences between semaphores, binary semaphores, and mutexes?
> A semaphore is essentially a counter with wait/post, a binary semaphore is a semaphore which only tracks "open/closed" and serves much of the same service as a mutex.

### What are the differences between channels (in Communicating Sequential Processes, or as used by Go, Rust), mailboxes (in the Actor model, or as used by Erlang, D, Akka), and queues (as used by Python)? 
> Channels define a communication line for a specific type than can be used for inter-thread communication (and IPC I believe). Mailboxes often accept different types and use the thread as the receiver (green thread in Erlang). Queues use a FIFO approach, and you have to handle the first message as opposed to in a mailbox approach where you can often pattern match against the incoming mail -- leaving some mail unread.  

### List some advantages of using message passing over lock-based synchronization primitives.
> Pattern match against incoming mail. Single communication line between parties which accept multiple types of data.

### List some advantages of using lock-based synchronization primitives over message passing.
> Granular control of synchronisation. Less overhead.