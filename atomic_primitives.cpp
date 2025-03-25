
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
/*
Atomic Primitives in C++

1. std::atomic and std::atomic_flag
std::atomic<T>
- A template that wraps around basic data types to make them thread-safe.
- Ensures reads/writes are atomic, meaning they can't be interrupted or seen partially by other threads.

std::atomic<int> counter{0};

// Safe concurrent increment:
counter.fetch_add(1);

Common Atomic Methods:
Method	Description
load()	Atomically read value
store(val)	Atomically write value
fetch_add(x)	Atomically add x
fetch_sub(x)	Atomically subtract x
exchange(x)	Atomically replace value and return old

std::atomic_flag

- A lightweight atomic boolean flag (true/false).
- Useful for building simple locks (like spinlocks), but also used in low-level lock-free patterns.

std::atomic_flag flag = ATOMIC_FLAG_INIT;

if (!flag.test_and_set()) {
    // do something only one thread should do
    flag.clear();
}

test_and_set() -> sets flag to true, returns previous value
clear() -> resets flag to false

2. std::atomic_compare_exchange_weak/strong
std::atomic<int> val{5};
int expected = 5;

bool success = val.compare_exchange_weak(expected, 10);

int expected = val.load();
while (!val.compare_exchange_weak(expected, 10)) {
    expected = val.load(); // Retry with updated value
}
Weak vs Strong
Version	Behavior
compare_exchange_weak	Can fail spuriously even if value matches (faster)
compare_exchange_strong	Fails only if value actually changed (slower, more reliable)

3. How Atomic Operations Replace Locks
Traditionally, threads use mutexes to synchronize access to shared data

With Locks (Blocking)
std::mutex mtx;
int counter = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    counter++;
}

Without Locks (Non-Blocking)
std::atomic<int> counter{0};

void increment(){
    counter.fetch_add(1);
}

*/