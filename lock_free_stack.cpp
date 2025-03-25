#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

template <typename T>
class LockFreeStack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::atomic<Node *> head;

public:
    LockFreeStack() : head(nullptr) {}

    void push(const T &value)
    {
        Node *new_node = new Node(value);

        // Keep trying until the CAS succeeds
        do
        {
            new_node->next = head.load(std::memory_order_relaxed);
        } while (!head.compare_exchange_weak(
            new_node->next, new_node,
            std::memory_order_release,
            std::memory_order_relaxed));
    }

    bool pop(T &result)
    {
        Node *old_head = head.load(std::memory_order_relaxed);

        // Keep trying until the CAS succeeds
        while (old_head != nullptr &&
               !head.compare_exchange_weak(old_head, old_head->next,
                                           std::memory_order_acquire,
                                           std::memory_order_relaxed))
        {
        }

        if (old_head == nullptr)
            return false;

        result = old_head->data;
        delete old_head;
        return true;
    }

    ~LockFreeStack()
    {
        T dummy;
        while (pop(dummy))
            ;
    }
};

int main()
{
    LockFreeStack<int> stack;

    // Push using multiple threads
    std::vector<std::thread> pushers;
    for (int i = 0; i < 4; ++i)
    {
        pushers.emplace_back([&stack, i]()
                             {
            for (int j = 0; j < 5; ++j) {
                stack.push(i * 10 + j); // Push values like 0, 1, 2... then 10, 11...
            } });
    }

    for (auto &t : pushers)
        t.join();

    // Pop everything in main thread
    int value;
    std::cout << "Popped values: ";
    while (stack.pop(value))
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
