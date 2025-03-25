
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
/*

In lock-free programming, data structures like stacks and queues are designed to allow multiple threads to operate concurrently—without blocking and using atomic operations only

1. Lock-Free Queue – Michael-Scott Queue (MSQueue)

What it is:
-A linked-list–based, multi-producer, multi-consumer queue.
-Proposed by Michael and Scott in 1996.
-Uses atomic operations to allow concurrent enqueue and dequeue.

Structure
head ---> Node ---> Node ---> Node ---> nullptr
                          ↑
                        tail

Key Concepts:
head and tail are atomic pointers
enqueue: adds to tail
dequeue: removes from head
*/
template <typename T>
class Node
{
public:
    T value;
    std::atomic<Node *> next;

    Node(const T &val) : value{val}, next(nullptr) {}
};

template <typename T>
class LockFreeQueue
{
private:
    std::atomic<Node<T> *> tail;
    std::atomic<Node<T> *> head;

public:
    LockFreeQueue()
    {
        Node<T> *dummy = new Node<T>(T{}); // dummy node
        head.store(dummy);
        tail.store(dummy);
    }

    void enqueue(const T &value)
    {
        Node<T> *new_node = new Node<T>(value);
        Node<T> *old_tail;

        while (true)
        {
            old_tail = tail.load();
            Node<T> *next = old_tail->next.load();

            if (old_tail == tail.load())
            {
                if (next == nullptr)
                {
                    if (old_tail->next.compare_exchange_weak(next, new_node))
                    {
                        break;
                    }
                }
                else
                {
                    tail.compare_exchange_weak(old_tail, next);
                }
            }
        }

        tail.compare_exchange_weak(old_tail, new_node);
    }
};

/*
 What are Hazard Pointers?
Hazard Pointers are a method where each thread declares which node it's currently accessing.
Nodes are only safely deleted when no thread is using them.
 How it works:
Before accessing a node, a thread stores a pointer to it in its hazard slot.
When deleting a node, you:
Check all hazard pointers.
Only delete it if no thread holds a hazard pointer to it.
 Key Concepts:
Lock-free data structures manage memory manually.
Hazard pointers make deferred memory reclamation safe
*/
