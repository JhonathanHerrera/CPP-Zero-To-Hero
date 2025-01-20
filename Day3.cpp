

#include <cstdint> // for fixed-width integers

#include <cstdlib>
#include <cstdint>
#include <iostream>
int main()
{

    /*Using cerr instead of cout can help ensure all debug output appears
    as soon as possible (at the cost of some performance,
    which we usually dont care about when debugging
    */
    std::cerr << "Hello" << '\n';

    /*The smallest unit of memory is a binary digit (also called a bit)
    , which can hold a value of 0 or 1.

    Memory is organized into sequences units called memory addresses
    (or addresses for short). Similar to how a street address can be used to find a given house on a street
    , the memory address allwos su to find and access the contents of memory
    at a particular location

    Each memory address hlds 1 byte of data, a byte is a group of bits that
    are operted on as a unit. The modern standard is that a byte is
    comprised of 8 sequential bits.

    Addreess 3 = [11101000]
    Addreess 2 = [00000000]
    Addreess 2 = [10010111]
    Addreess 1 = [01101001]

    An incompletet type is a type that has been decalred but not yet
    defined. The complier knwos about the existence of such types, but
    does not have enough information to determine how much memory to allocate
    for objects of that type. void is itentioanlly incompletet isnce it respresnetns the lack
    of a type, and thus cannot be defined

    char = 8, short = 16, int = 32 (16 in some systems), long = 64, long long = 64

    Signed integers = Attribute of being positive, negative, or zero

    By default, intergers in C++ are signed

    In C++20 standard makes this blankets statement "If during
    the evaluation of an expression, the result is not mathematically defined or not
    in the range of representable values for its type, the behavior
    is undefiend" Colloquially this is called overflow


    If an arithemic operiaotn (such as addition or multiplication
    ) attempts to create a value of outside the range that can be respresnted, this is
    called integer overflow (or arithmetic overflow). For signed integers, integer
    overflow will result in underfined behavior

    */

    // To define an unsigned integer, we use unsigned keyword
    unsigned short unsigned_integer;

    // 1-byte unsigned inetger has a range of 0 to 255
    // While signed has a range of -129 to 127

    /*
    8 bit unsigned = 0 to 255
    16 bit unsigned = 0 to 65,535
    32 bit unsigned = 0 to 4,294,967,295
    64 bit unsigned = 0 to 18,446,744,073,709,551,615

    What happens if we try to sotre the  number 280 (which
    requieres 9 bits to represent) in a 1-byte (8-bit) unsigned integer?
    The answer is overflow
    */

    /*
     Because the size of these integersnis fixed, they are called
     fixed-width itegers

     Integers are great for couting whole numbers, but sometimes we need to
     store very large numbers, or numbers with a fractional component.
     A floating point type variable is a variable that can hold a number
     with a fractional component.

     The kind of sentence that pnly have two possible outcomes: yes/true
     , or no/false are known as Boolean

     The char data type was designed to hold a single character
     A character can be a single letter, number, symbol, or whitespace
    */

    std::cout << sizeof(long long) << '\n';
    std::int32_t x{32767}; // x is always a 32 bit integer
    float c{5.0f};
    bool b{};  // default initialize to false
    x = x + 1; // so 32768 will always fit
    std::cout << x << '\n';

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << static_cast<int>(5.5); // explicaitly convert doubl val to int
    return EXIT_SUCCESS;
}