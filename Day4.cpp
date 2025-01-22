#include <iostream>
#include <bitset> // for std::bitset
#include <string>
#include <string_view>
#include <format>
#include <cmath>

void someFnc()
{
#define gravity 9.8
}

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

// void printGravity(double gravity) // including this one, causing a compilation error
void printGravity()
{
    std::cout << "gravity: " << gravity << '\n';
}

int main()
{

    /*
    In programming, a constant is a value that may not be changed durting the program's
    execution. C++ supports two different kinds of constatnt

    1) Named constants = assocaited with an indentifier (also called  symbolic constants)
    2) Literal constants = are not associated with an identifier

    const before the type is more conventional

    const double gravity; // error: const variables must be initialized
    gravity = 9.9;        // error: const variables can not be changed

    function parameter can also have constants paramter

    void printInt(const int x)

    A magic number is a literal (usually a number) that either has an unclear meaning or may need to
    be changed later

    Octal is base 8 - that is the only digits available are: 0 1 2 3 4 5 and 7 (skip 8 and 9)

    int x{012}; 0 before the number means this is octal and itll output 10

    Hexadecimal is base 16
    int x{0xF}; 0x before the number means this is hexadecimal

    int bin {};
    bin = 0xF770 = 1111 0111 0111 0000
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    // std::bitset<8> means we want to store 8 bits
    std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101

    Optimization is the process ofmodifying software to make it work more efficiently (to run faster
    or use fewer resources)

    Some types of optimization are typically done by ahdn. a program called a profiler can be used
    to see how long various parts of the program are taking to run, and which are impacting overall performance

    A　program that optimizes another program is called an optimizer, typically work at a low level
    , looking for ways to improves statement or expression by rewriting, reordering, or elimanting them

    when i write i = i * 2, the optimizer might write it as i *= 2

    */

    // std::cout << std::format("{:b}\n", 0b1010); // C++20, {:b} formats the argument as binary digits
    // std::println("{:b} {:#b}", 0b1010, 0b1010); // C++23, format/print two arguments (same as above) and a newline

    /*
    The as-if rule says that the compiler can modify a program however it likes in order to produce
    more optimized code

    One of the original forms of compile-time evaluation is called "constant folding" which
    is aoptimzation technioque where the compiler repalces expressions that have literal
    operands with the result of the expression

    Constants propagation is an optimization technqieu where theccompiler replaces variables known to have\
    to have constant values with their values.

    Dead code elimantion is an optimization technique where the complier removes code that may be executed but has no effect on the
    program's behavior

    int x {7}; this x variable is the dead code
    std::cout << 7 <<

    constexpr keyword

    A constexpr variable is always a compile-time constant.

    const vs constexpr
    const = variable is a value that cannot be changed after initialization
        - it can be set either before or while the program runs
    constexpr = variable is a compile-time constant
        -the value must be known before the program runs

    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    constexpr int m3 { cmax(5, 6) }; // okay: must evaluate at compile-time

    for string, if we have "Alex" it contains 5 characters (four explicit chaacters and a null-terminator)

    If std::string doesn’t have enough memory to store a string, it will request additional memory (at runtime)
     using a form of memory allocation known as dynamic memory allocation.
     This ability to acquire additional memory is part of what makes std::string so flexible, but also comparatively slow.

     operator>> only returns characters up to the first whitespace which is why std::cin cant get a full name

     thats why you use getline(), it has two parameters

    string vs string_view

    1. Owndership
        -string owns the string data it holds, it mangers memory meaning it allocates, resize, and
        deallocates memory as needed
        -string view does not won the string data, its a non-owning refernce to a string or a part of a string
        . its essentially a lightweifght view into existing string data, which means it doesnt manage or allocate memory

    2. Performance
        -string has manipulation like copying or slicing involve memeory allocation and copying
        .better suited for scenarios where the string needs to be modified or manage independently
        -string view does not won the string data. it is a non owning referncce to a string or
        a part of a string. it is essentially a lightweifght view into existing string data,
        which means it does not manage or allocate memory.
    3. mutability
        -string you can modify the content
        -strgin view cannot modify the string
    4. use cases
        -string when you need to own, modify, or store the string data. when dynamic allocation
        and resizing are required/
        - string view when you need a lightweight, read-only view inot an existing string or
        a part of it (parsing substrings). when passing strings to functions to avoid unnecessary copying
    */

    std::string name{};
    std::getline(std::cin >> std::ws, name);

    std::string str1{"Jhonathan"};
    std::string_view str2{str1}; // str2 does not own str1, but instead we are viewing it
                                 //  without allocating memory
    std::string_view str3{str2.substr(0, 5)};

    std::cout << str1 << " " << str2 << " " << str3 << std::endl;

    /*

    An operation is a mathematical process involving zero or more input values (called operandas) that produces a
    new value (called an outpout value) he specific operation to be performed is denoted by a construct (typically a symbol or pair of symbols) called an operator.

    The C++ standard uses the term value computation to mean the execution of operators in an expression to produce a value. The precedence and association rules
    determine the order in which value computation happens.

    The C++ standard (mostly) uses the term evaluation to refer to the evaluation of operands

    The remainder operator (also commonly called the modulo operator or modulus operator)

    Increment/Decrement operators, and side effects *IMPORTANT*

    Prefix increment (pre-increment) = ++x	Increment x, then return x
    Prefix decrement (pre-decrement) =  ––x	Decrement x, then return x
    Postfix increment (post-increment) = x++	Copy x, then increment x, then return the copy
    Postfix decrement (post-decrement) =	x––	Copy x, then decrement x, then return the copy

    */

    std::cout << 7.0 / 4 << '\n'; // this will return 1.75
    std::cout << 7 / 4 << '\n';   // this will return 1

    int x{5};
    int y{++x}; // x is incremented 6, x evaluate to the value 6, and 6 is assigned to y

    std::cout << x << " " << y << '\n'; // 6 6

    int z{x++};

    std::cout << x << " " << z << '\n'; // 7 6

    int _x{5};
    int _y{5};
    std::cout << _x << ' ' << _y << '\n';
    std::cout << ++_x << ' ' << --_y << '\n'; // prefix
    std::cout << _x << ' ' << _y << '\n';
    std::cout << _x++ << ' ' << _y-- << '\n'; // postfix
    std::cout << _x << ' ' << _y << '\n';

    int max{};

    if (x > y)
        max = x;
    else
        max = y;

    // This can also be written as

    max = ((x > y) ? x : y);

    return 0;
}
