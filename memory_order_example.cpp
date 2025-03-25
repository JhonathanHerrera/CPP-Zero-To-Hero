#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Shared data
std::atomic<bool> ready_relaxed(false);
std::atomic<bool> ready_release_acquire(false);
std::atomic<bool> ready_seq_cst(false);

std::atomic<int> orderCounter(0); // Used with acq_rel
int food = 0;                     // Not atomic on purpose (to show effect of memory order)

//  Unsafe - Relaxed version
void cookWithRelaxed()
{
    food = 10;                                            // Cook food
    ready_relaxed.store(true, std::memory_order_relaxed); // Signal ready
}

void serveWithRelaxed()
{
    while (!ready_relaxed.load(std::memory_order_relaxed))
        ; // Wait
    std::cout << "[RELAXED] Served food: " << food << " (could be wrong)\n";
}

//  Safe - Release/Acquire version
void cookWithRelease()
{
    food = 20;
    ready_release_acquire.store(true, std::memory_order_release); // Signal ready
}

void serveWithAcquire()
{
    while (!ready_release_acquire.load(std::memory_order_acquire))
        ; // Wait
    std::cout << "[RELEASE/ACQUIRE] Served food: " << food << " (should be 20)\n";
}

//  Safe - Seq_cst (strongest)
void cookWithSeqCst()
{
    food = 30;
    ready_seq_cst.store(true, std::memory_order_seq_cst); // Signal ready
}

void serveWithSeqCst()
{
    while (!ready_seq_cst.load(std::memory_order_seq_cst))
        ; // Wait
    std::cout << "[SEQ_CST] Served food: " << food << " (should be 30)\n";
}

//  Safe - Atomic counter using acq_rel
void placeOrders(int id)
{
    for (int i = 0; i < 3; ++i)
    {
        int orderNum = orderCounter.fetch_add(1, std::memory_order_acq_rel);
        std::cout << "[Thread " << id << "] Placed order #" << orderNum << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main()
{
    std::cout << " Testing different memory orders...\n";

    // RELAXED (may give wrong result)
    std::thread t1(cookWithRelaxed);
    std::thread t2(serveWithRelaxed);
    t1.join();
    t2.join();

    // RELEASE/ACQUIRE (correct)
    std::thread t3(cookWithRelease);
    std::thread t4(serveWithAcquire);
    t3.join();
    t4.join();

    // SEQ_CST (correct)
    std::thread t5(cookWithSeqCst);
    std::thread t6(serveWithSeqCst);
    t5.join();
    t6.join();

    // ACQ_REL counter
    std::cout << "\n Simulating order placement using acq_rel...\n";
    std::thread t7(placeOrders, 1);
    std::thread t8(placeOrders, 2);
    t7.join();
    t8.join();

    std::cout << " Done testing memory orders.\n";
    return 0;
}
