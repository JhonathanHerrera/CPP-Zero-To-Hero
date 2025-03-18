#include <memory>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdio>

/*

Why use a custom deleter?
1) Working with C APIs (ex: FILE*, fclose())
2) Using malloc() instead of new (so we need free())
3) Handling non-standard resource cleanup (ex: closing database connections)

1 : Using a Custom Deleter for C APIs (fclose)

- Many C APIs return pointers that need to be manually freed (e.g., fopen() returns a FILE* that must ne closed with fclose())

Example #1 (1/2)

Why is this used in industry?
- Many APIs return pointers that must be manually freed (like fopen(), socket(), etc)
- Avoids forgetting to call fclose(), reducing resource leaks

Where is this used?
- File I/O
- Network sockets
- Database conenctions(ex, sqlite3_close())

2 : Using a Custom Deleter for malloc()

- If memory is allocated with malloc(), it must be freed with free(), not delete

Example #2 (1/2)

Why is this used in industry?
- Some C librarires (like CUDA, OpenCL, or legacy C codebasese) use malloc() instead of new
- Using delete on malloc() - allocated memory causes undefined behavior

Where is this used?
-Interfacing with legacy C libraries
- Memory allocated via external allocators (e.g., posix_memalign())

3 : Using a Function (Class) for More Complex Cleanup

In some cases, a simple lambda isn’t enough, and a class with operator() (a functor) is used.

Example #3 (1/3)

Why is this used industry?
- For complex cleanup logic (e.g., logging, error handling).
- Easier to reuse across multiple objects.
- Used when a lambda would be too long or difficult to manage.

Where is this used?
- Resource management classes
- RAII-based APIs
- Game engine, database conencitons, GPU allocations


*/

// Example #3 (2/3)

struct CustomDeleter
{
    void operator()(int *ptr)
    {
        std::cout << "Deleting int: " << *ptr << std::endl;
        delete ptr;
    }
};

int main()
{

    // Example #1 (2/2)
    auto fileDeleter = [](FILE *f)
    {
        if (f)
        {
            std::cout << "Closing file\n";
            fclose(f);
        }
    };

    std::unique_ptr<FILE, decltype(fileDeleter)> file(fopen("example.txt", "w"), fileDeleter);

    if (!file)
    {
        std::cerr << "Failed to open file!\n";
        return 1;
    }

    std::cout << "Writing to file ...\n";
    fprintf(file.get(), "Hello, World!");

    // Example #2 (2/2)
    auto mallocDeleter = [](void *ptr)
    {
        std::cout << "Freeing memory\n";
        free(ptr);
    };

    std::unique_ptr<int, decltype(mallocDeleter)> uptr(static_cast<int *>(malloc(sizeof(int))), mallocDeleter);

    if (uptr)
    {
        *uptr = 123;
        std::cout << "Value: " << *uptr << std::endl;
    }

    // Example #3 (3/3)
    std::unique_ptr<int, CustomDeleter> uptr(new int(100));

    return 0;
}