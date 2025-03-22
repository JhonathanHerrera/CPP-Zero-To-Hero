#include <iostream>
#include <atomic>

/*

When you're writing multi-threading programs, your CPU and compiler can reorder
instructions to optimize speed

Thats fine for single-threaded code, but in multi-threaded programs, instructions reordering can break your assumptions:
One thread writes a value, another thread reads it - but sees an old or unitialized value bcause things were reordered

What Memory Order Does -

Memory orders control the visibility and ordering of operations betwenn threads
They tell the CPU and compiler how strictly


Avaible Memory Orders in C++

Memory Order	Description
memory_order_relaxed	Fastest, no guarantees — good for counters
memory_order_acquire	Prevents reads before the load from moving after
memory_order_release	Prevents writes after the store from moving before
memory_order_acq_rel	Combines acquire + release
memory_order_seq_cst	Strongest, sequentially consistent (default)



*/

int main()
{

    // Thread A
    std::atomic<bool> ready(false);
    int data = 0;
    data = 42;
    ready.store(true, std::memory_order_release); // publish data

    // Thread B
    while (!ready.load(std::memory_order_acquire))
        ;                           // wait
    std::cout << data << std::endl; // safe to read

    // memory_order_relaxed
    //  - Fastest
    //  - X  No guarantee about order or visibility
    //  Use for : counters, metrics
    std::atomic<int> count(0);
    std::atomic<int> counter(0);

    std::atomic<int> flag(0);
    count.fetch_add(1, std::memory_order_relaxed);

    // memory_order_acquire (used on load)
    //- ensures all reads/writes after this wont be ordered before it
    //- use on loads to see what other thread wrote before releasing

    while (!flag.load(std::memory_order_acquire))
        ;

    // memory_order_release (used on store)
    //  - Ensures all reads/writes before this happen-before the store
    //  - use when publishing data to other threads
    data = 123;
    flag.store(true, std::memory_order_release);

    // memory_order_acq_rel (used on RMW ops)
    //  - combines acquire + release
    //  - use when you're reading and writing atomically (like fetch_add, compare_exchange)
    counter.fetch_add(1, std::memory_order_acq_rel);

    // memory_order_seq_cst (Default)
    //  - sequential consistency: all threads agree on a single total order of operations
    //  - easiest to reason about, safest - but may be slower
    flag.store(true); // same as store(..., std::memory_order_seq_cst)

    /*

    Use Case	Memory Order
    Atomic counters only	memory_order_relaxed
    One thread writes data, another waits on flag	release / acquire
    Reading and writing atomically	acq_rel
    You want simple and safe behavior	seq_cst (default)
    */

    return 0;
}
