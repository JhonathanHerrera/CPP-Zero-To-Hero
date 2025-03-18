#include <iostream>

// Memory Pool and preallocaiton

/*
What are theissues with regular allocation? (malloc/calloc)
- slower perormnace -> calls to malloc or calloc take time
- memory fragmentation -> if objects are allocated and dealloacted requently, memory becomes fragmented
- unpredictable behavior -> in real-time systems, memory allocation must be fast

What is Preallocation?
- Prealloation means reserving memory before you need it. so you can reuse it later
without asking the OS for more memory

How it works?
1. instead of calling malloc() every time, allocate a large block once
2. keep track of free memory inside that block
3. when memory is needed, give a piece of the reallocated block
4. when memory is freed, return it to the pool for reuse

*/

class MemoryPool
{

private:
    struct Block
    {
        Block *next; // Pointer to the next free block
    };

    Block *freeList; // Keep track of free mrmory
    void *pool;
    size_t blockSize;
    size_t poolSize;

public:
    // Constructor: Allocate memory at the start
    MemoryPool(size_t blockSize, size_t numBlocks) : blockSize(blockSize), poolSize(numBlocks)
    {
        pool = std::malloc(blockSize * numBlocks); // Allocate memory ONCE
        freeList = static_cast<Block *>(pool);

        // Create a linked list of free memory blocks
        Block *current = freeList;
        for (size_t i = 1; i < numBlocks; ++i)
        {
            current->next = reinterpret_cast<Block *>(reinterpret_cast<char *>(current) + blockSize);
            current = current->next;
        }
        current->next = nullptr; // Last block points to null
    }

    // Allocate memory from the pool
    void *allocate()
    {
        if (!freeList)
        {
            throw std::bad_alloc(); // No avaiable memory
        }
        Block *allocatedBlock = freeList;
        freeList = freeList->next; // Move to the next free block
        return allocatedBlock;
    }

    // Deallocate memory back to the pool
    void deallocate(void *ptr)
    {
        Block *returnedBlock = static_cast<Block *>(ptr);
        returnedBlock->next = freeList; // Return the block to the free list
        freeList = returnedBlock;
    }

    // Function to print the number of free blocks
    void printFreeBlocks()
    {
        int count = 0;
        Block *current = freeList;
        while (current)
        {
            count++;
            current = current->next;
        }
        std::cout << "Free blocks available: " << count << "/" << poolSize << std::endl;
    }

    // Destructor: Free the entire memory pool
    ~MemoryPool()
    {
        std::free(pool);
    }
};

int main()
{

    MemoryPool pool(32, 5); // Create a pool of 5 blocks (32 bytes each)
    pool.printFreeBlocks();

    void *p1 = pool.allocate(); // Grab a block
    pool.printFreeBlocks();

    void *p2 = pool.allocate();
    pool.printFreeBlocks();
    pool.deallocate(p1);
    pool.printFreeBlocks();

    std::cout << "Allocated memory: " << p1 << " and " << p2 << std::endl;

    pool.deallocate(p1); // Return memory to the pool
    pool.deallocate(p2);

    std::cout << "Memory returned to pool!" << std::endl;

    return 0;
}