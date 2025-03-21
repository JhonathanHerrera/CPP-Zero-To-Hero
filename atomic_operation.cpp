#include <iostream>
#include <thread>
#include <atomic>

/*

What Are Atomic Operation?

An atomic operation is an action that is:

- uninterruptible
- thread-safe by default
- happens "all at once" - no other thread can see it partially complete

with atomic types, you dont need mutexes to safetly share variables between threads

Why use std::atomic?

- avoids data races without locks
- enables lock-free programming
- great for high-peroformance concurrent applications (like for trading engines)

Compare-and-Swap (CAS) - compare_exchange_weak/strong

What is CAS?

- A low-level operation used to update a value only if it matches the expected old value
- "If this variable is still X, change it to Y - otherwise, do nothing"

compare_exchange_weak vs. compare_exchange_strong

compare_exchange_weak -> May fail spuriously, meant for use in loops
compare_exchange_strong -> Only fails if the value actually doesn't match

use weak in tight loops for performance
use strong when you need it to be corredct (less efficient)

Aspect	compare_exchange_weak	compare_exchange_strong
Can fail spuriously?	Yes — may fail even if values match	 No — only fails if values don't match
Intended usage	In loops, where performance is critical	When you must be sure it only fails if not equal
Performance	Slightly faster on some platforms (more optimized)	Slightly slower, more reliable
Reliability	May need multiple retries (use in a loop)	Usually works in 1 try if values match

 What does compare_exchange_weak give us?

It lets you safely update a shared value between threads without using a mutex — meaning:
- Faster
- No locking / unlocking
- Thread-safe

Benefits of compare_exchange_weak

Benefit	Explanation
Lock-free	No std::mutex, no overhead of locks
Safe under race conditions	Automatically retries if another thread changes the value
Fast	Especially on systems like your M2 chip (ARM architecture)
Perfect for shared data structures

 Why use this over counter = 10 or a mutex?

counter = 10 → Not safe if another thread is writing/reading at the same time.
std::mutex → Safe, but slower due to locking/unlocking.

Memory Ordering - std::memory_order

Threads may reorder memory operations for optimization. This can cause
unexpected behavior in multi-threaded programs

std::atomic allows you to control memory visibility between threads.

memory_order_relaxed	No ordering constraints (fast but unsafe unless used carefully)
memory_order_acquire	Prevents reordering of reads before the atomic
memory_order_release	Prevents reordering of writes after the atomic
memory_order_acq_rel	Combines acquire + release
memory_order_seq_cst	Default, strongest ordering (safe and simple)

When to Use Atomics over mutexes

Use Atomics When...               Use Mutexes When...
1) simple shared variables        1) Complex critical sections
2) high - performance counters    2) Need to protect multiple vars together
3) lock-free algorithms           3) Code is easier with locks

*/

std::atomic<int> counter(0); // atomic shared counter

void increment()
{
    for (int i = 0; i < 1000; ++i)
    {
        counter++;
    }
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();
    std::cout << "Final Couter: " << counter << std::endl;

    std::atomic<int> value(5);
    int expected = 5;
    int desired = 10;

    if (value.compare_exchange_strong(expected, desired))
    {
        std::cout << "Value was 5, changed to 10\n";
    }
    else
    {
        std::cout << "Value was not 5, so no change\n";
    }
    std::cout << "Current value: " << value << std::endl;
    return 0;
}