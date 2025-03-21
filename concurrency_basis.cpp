
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/*

What are Threads and Processes?
- Process: A process is an instance of a program that is running on your computer.
Each process has its own memory and resources. For Example, when you open Google Chrome, it runs as a seperate process.

- Thread: A threa is a smaller unit of execution within a process. A process can have multiple threads,
which share the same memory but can execute tasks independently

Think of a process as a restaurant (the whole program) and threads as chefs (tasks within the program). If there’s only one chef,
orders will be slow. If there are multiple chefs (threads), they can prepare multiple dishes at once, making things faster.

2. Threads in C++ (std::thread)

1) std::thread t(printMessage); -> this creates a new thread t that runs printMessage()
2) t.join() -> the main program waits for t to finish before continuing
3) If we dont use join(), the main program might finish before printMessage() gest executed

3. Creating and Joining Threads

4. Thread Safety Issues
When multiple threads share resources (e.g., variables), they can interfere with each other, leading to race conditions and data corruption.

5. Fixing Thread Safety Ussues using std::mutex

std::mutex mtx; → Creates a mutex.

std::lock_guard<std::mutex> lock(mtx); → Locks the mtx when modifying counter, preventing simultaneous updates.

Mutexes & Locks in C++

6. Why do we need mutexes?

- When multiple threads access shared data at the same time, they can cause race conditions, leading to incorrect results.
For example, if two threads are modifying a shared variable at the same time, the final value may be unpredictable.

7. Mutex (std::mutex)
- A mutex (mutual exclusion) ensures that only one thread accesses a shared resource at a time.

8. std::lock_guard (Automatci Mutex Handling)

Using mtx.lock() and mtx.unlock() manually is error-prone. If an exception occursm the mutex may not be unlocked
- std::lock_guard<std::mutex> automatically locks and unlocks the mutex.

9. std::unique_lock (More Flexible)

If you need more control, use std::unique_lock<std::mutex>, which allows

1. Deferred locking (lock later)
2. Locking & unlocking manually
3. Moving ownership of locks

10. Deadlocks and How to avoid them
- Deadlocks occurs when two or more threads wait on each other, and execution halts forever

11. Avoiding Deadlocks

Solution 1) Always Lock Mutexes in the Same Order
- If all threads always lock mutexes in the same order, deadlocks wont occur

Solution 2) Use std:try_lock
- std::try_lock doesnt block- if it cants lock a mutex, it moves on

12. std:condition_variable

Why do we need it?
 - a conditional variable allows one or more threads to wait (pause execution) until a condition is met

Without condition variables:
    - A thread that needs some data must continuously check (polling), which wastes CPU cycle

With Condition variables:
    - The thread sleeps until notified, making it efficient,

13. basic usage of condition_variable
- wakes up a waiting thread when the condition is met
*/

int counter = 0;      // shared resource
std::mutex mtx;       // Mutex to protect counter
std::mutex print_mtx; // Mutex to protect counter
std::mutex unique_lock;
std::condition_variable cv;

void uniqueLockFunction()
{
    std::unique_lock<std::mutex> lock(unique_lock);

    // Do something
    lock.unlock();
}

void printMessage()
{
    std::cout << "This is a thread" << std::endl;
}

void task(int id)
{
    std::lock_guard<std::mutex> lock(print_mtx); // Lock cout
    std::cout << "Thread " << id << " is runing" << std::endl;
}

void increaseCounter()
{
    for (int i = 0; i < 1000; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx); // Locks the critical section
        counter++;
    }
}
int main()
{

    // Create a thread that runs the printMessage function
    // std::thread t(printMessage);
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    // Wait for the thread to finish execution
    // t.join();
    t1.join();
    t2.join();

    std::thread t3(increaseCounter);
    std::thread t4(increaseCounter);

    t3.join();
    t4.join();

    std::cout << "Counter: " << counter << std::endl;

    return 0;
}