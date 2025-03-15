#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <class T>
class unique_ptr
{

public:
    unique_ptr() noexcept : unique_ptr{nullptr} {}

    // explicit prevents implicit conversions, meaning you cant convert data types
    explicit unique_ptr(T *ptr) noexcept : m_ptr{ptr} {}

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    // Move constructor
    unique_ptr(unique_ptr &&other) noexcept : m_ptr{other.release()} {}
    /*
    -moves ownership of the resource from other to this
    -calls other.release() which:
        1) returns the pointer managed by other
        2) sets other.m_ptr to nullptr, ensuring other no longer manages the resource
    -the moved-from object (other) becomes empty (nullptr)

    */

    // Move assignment operator
    unique_ptr &operator=(unique_ptr &&other) noexcept
    {
        if (this != &other)
        {                           // avoid self-assignment
            reset(other.release()); // transfer ownership
        }
        return *this;
    }
    /*

    - unique_ptr &&other means that other is an rvalue reference, meaning it cannot be a named variable but must be something that is being "moved" (temporary object)
    - Transfers ownership only if this is not the same object as other (this != &other avoids self-assignment)
    - Calls reset(other.release()):
        1) releases ownership of the current objecet (deletes the old pointer)
        2) takes ownership of other's resource
    - Returns *this to allow chaining

    */

    // allows if (p)
    // unique_ptr can be used in an if statement
    // converst unique_ptr to true if it owns a pointer, and false if it's nullptr
    explicit operator bool() const noexcept
    {
        return static_cast<bool>(m_ptr);
    }

    // Return the raw pointer stored inside unique_ptr without transferring ownership
    // useful if you need the raw pointer for certain API calls
    T *get() const noexcept { return m_ptr; }

    // p->... calls ((p).operator->())->...
    // Allows unique_ptr to behave like a regular pointer whne accesssing object memebers
    // Enables p->member instead of (*p).member
    T *operator->() const noexcept { return m_ptr; }

    /*
   Example:
   struct Example {
       void sayHello() { std::cout << "Hello, world!" << std::endl; }
   };

   unique_ptr<Example> uptr(new Example);
   uptr->sayHello(); // Works like a regular pointer
   */

    // *p calls ((p).opeartor*())
    // Allows dereferencing unique_ptr just like a raw pointer (*ptr)
    // Returns a reference to the object managed by unique_ptr
    T &operator*() const noexpect { return *m_ptr; }

    // For giving up ownership
    T *release() noexcept
    {
        return std::exchange(m_ptr, nullptr);
        // T* old = m_ptr;
        // m_ptr = nullptr;
        // return old
    }

    void reset(T *ptr = nullptr) noexcept
    {
        T *old = std::exchange(m_ptr, ptr);
        if (old)
        {
            delete old;
        }
    }

    ~unique_ptr() noexcept
    {
        if (m_ptr)
        {
            delete m_ptr;
        }
    }

private:
    T *m_ptr;
};