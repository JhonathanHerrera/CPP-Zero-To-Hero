
#include <iostream>
#include <thread>
#include <mutex>

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
*/

int counter = 0;      // shared resource
std::mutex mtx;       // Mutex to protect counter
std::mutex print_mtx; // Mutex to protect counter

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