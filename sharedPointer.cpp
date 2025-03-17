#include <iostream>
#include <memory>

/*
1. Introduction to std::shared_ptr?

std::shared_ptr is a smart pointer that enables shared ownership of an object. When multiple shared_ptrs point to the
same resource, the resource is automatically deleted when the olast owner goes out of scope. So when the counter goes to 0

Key Features:
- Uses reference counting to track ownership
- Automatically deallocates memory when no shared_ptr owns the object
- supports copying and assignment, unlike std::unique_ptr
- can be used with std::weak_ptr to prevent circular references

When to use std::shared_ptr?
- when multiple parts of a program share wonership of an object
- when you want autoamtic resource mangement without manually freeing memory
- when you need exceptionsafety (no memory leaks on early return)

2. Creating and using std::shared_ptr

The best way to create a std::shared_ptr is using std::make_shared<T>(args...), which is more efficient than using new directly

Why std::make_shared?
- more efficient (creates both the contorl block and object in a single memory allocation)
- avoids potential memory leaks due to exceptions between allocation and shared_ptr initialization

3. Reference Counting (use_count)

Each std::shared_ptr maintains a reference count that tracks how many shared_ptrs are pointing to the same object

4. Copying and Assigning std::shared_ptr
- since std::shared_ptr allows multiple owners, it supports copy and assignment

5. Passing std::shared_ptr to Functions
- When passing a std::shared_ptr to a function, you should decide ownership behavior:
    1) Pass by value (shared_ptr<T>) -> increase reference count
    2) Pass by reference (const share_ptr<T>&) -> Avoids increasing reference count

6. std::weak_ptr - Solving circulare references
- A major drawback of std::shared_ptr is circular refernces, where two objectsb hold shared_ptrs to each other,
preventing deletion

7. Performance Considerations
- std::shared_ptr adds overhead due to reference counting
- prefer std::unique_ptr when exclusive ownership is needed
- std::make_shared is more efficient than new

*/

// Example 1

class MyClass
{
public:
    MyClass(int val) : value(val)
    {
        std::cout << "Constructor called: " << value << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
    }

    ~MyClass()
    {
        std::cout << "---------------------------------------------------------------------------" << std::endl;

        std::cout << "Destructor called: " << value << std::endl;
    }

    void show()
    {
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << "Value: " << value << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
    }

private:
    int value;
};

// Example 4: Pass by Reference (Efficient) 1/2
void display(const std::shared_ptr<int> &sp)
{
    std::cout << "Value: " << *sp << ", Use cont: " << sp.use_count() << std::endl;
}

// Example 5: Curcular Reference Problem (1/2)

class B; // Forward declaration

class A
{
public:
    std::weak_ptr<B> bptr;
    ~A()
    {
        std::cout << "A  destroyed" << std::endl;
    }
};

class B
{
public:
    std::weak_ptr<A> aptr;
    ~B()
    {
        std::cout << "B  destroyed" << std::endl;
    }
};

int main()
{

    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(10);
    ptr1->show();

    std::cout << "Use count: " << ptr1.use_count() << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;

    // Example 2: Multiple Owners
    std::shared_ptr<int> obj1 = std::make_shared<int>(10);
    std::shared_ptr<int> obj2 = obj1;

    std::cout << "Use count after obj2: " << obj1.use_count() << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;

    {
        // New scope for the obj3
        std::shared_ptr<int> obj3 = obj1;
        std::cout << "Use count after obj3: " << obj1.use_count() << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
    }
    std::cout << "Use count after obj3 is out of the scope : " << obj1.use_count() << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;

    // Example 3: Copying std::shared_ptr
    std::shared_ptr<int> copyPtr1 = std::make_shared<int>(100);
    std::shared_ptr<int> copyPtr2 = copyPtr1;

    std::cout << "The use count of the copy poitners are: " << copyPtr1.use_count()
              << " and the values of each pointers are: copy Pointer1: [" << *copyPtr1 << "] || copy Pointer2: ["
              << *copyPtr2 << "]" << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;

    // Example 4: Pass by Reference (Efficient) 2/2
    std::shared_ptr<int> ref = std::make_unique<int>(50);
    display(ref);

    std::cout << "Use count after function call: " << ref.use_count() << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;

    // Example 5: Curcular Reference Problem (2/2)
    std::shared_ptr<A> a = std::make_unique<A>();
    std::shared_ptr<B> b = std::make_unique<B>();

    a->bptr = b;
    b->aptr = a; // Circular reference (memory leak), thats why we changed to a weak_ptr

    return 0;
}