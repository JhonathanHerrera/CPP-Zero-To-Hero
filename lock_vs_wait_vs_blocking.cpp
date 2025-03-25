

/*

Lock-Free vs. Wait-Free vs. Blocking Algorithms

These are three categories of concurrent algorithms, and understanding them is key for building high-performance, multi-threaded applications (like trading engines, databases, or real-time systems).

1. Blocking Algorithms (Traditional Locks)
What It Is:

- Uses mutexes, condition variables, or semaphores to synchronize threads.
- If a thread can’t access a resource, it gets blocked (suspended) and waits.

std::mutex mtx;
void criticalSection() {
    std::lock_guard<std::mutex> lock(mtx); // thread blocks if mtx is held
    // safely access shared data
}

 Pros:
Simple and safe.
Easy to reason about.
Well-supported and well-understood.
 Cons:
Can cause deadlocks, livelocks, and priority inversion.
Context switching is expensive when many threads are blocked.
Doesn’t scale well with many cores or low-latency requirements.

 2. Lock-Free Algorithms

 What It Is:
No threads are blocked.
At least one thread always makes progress.
Uses atomic operations like compare_exchange, fetch_add, etc.
 Example:
A lock-free push to a queue:
std::atomic<Node*> head;

void push(int value) {
    Node* newNode = new Node(value);
    do {
        newNode->next = head.load();
    } while (!head.compare_exchange_weak(newNode->next, newNode));
}

 Pros:
Higher performance under contention.
Avoids deadlocks.
Good for real-time systems and high-frequency trading.
 Cons:
Harder to design and debug.
Still susceptible to livelocks (e.g., threads spinning indefinitely).
Complex memory management (e.g., hazard pointers or epoch reclamation).

3. Wait-Free Algorithms
 What It Is:
Stronger than lock-free.
Every thread is guaranteed to complete its operation in a finite number of steps, regardless of others.
 Example:
Designing a wait-free queue means every enqueue/dequeue is guaranteed to succeed within a few steps, no matter what other threads do.
 Pros:
Hard real-time safety: No starvation.
Maximum fairness.
Best for systems that can’t afford delays (e.g., aerospace, medical devices).
 Cons:
Very difficult to design.
May be less efficient in practice than lock-free due to overhead.
Rarely needed outside real-time or critical systems.

Summary Table

Feature         |     	Blocking	  | Lock-Free  |	Wait-Free
Thread blocking	|           Yes       | 	No	   |         No
Fairness	    |             Depends |   	Maybe  |    Guaranteed
Throughput	    |Low under load	      | High	   |Medium-High
implementation	|Easy                 |	Hard	    |Very Hard
Deadlock possible?	Yes	              |No           |	No
Starvation possible?  Yes	          | Yes     	|No
Use case examples	General apps, CLI |Trading engine| logging	Real-time OS, avionics

Why Use Lock-Free or Wait-Free Programming?

 Lock-Free is ideal when:
You care about low-latency and high-throughput (e.g., HFT, game engines).
You want to avoid blocking I/O or context switches.
You’re dealing with massive thread contention.
 Wait-Free is ideal when:
You need absolute guarantees of progress.
You're building real-time or mission-critical systems.


Compare-and-Swap (CAS) – The Heart of Lock-Free
// Pseudocode for CAS:
if (current_value == expected_value) {
    current_value = new_value;
    return true;
} else {
    return false; // try again later
}
std::atomic<int> val{5};
int expected = 5;
val.compare_exchange_weak(expected, 10); // sets val to 10 if val was 5


*/