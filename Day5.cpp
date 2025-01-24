#include <iostream>
#include <bitset>

int main()
{

    /*
        TIME TO DO BIT MANIPULATION!
        A byte is 8 bits

        Modifying individual bits within an object is called bit manipulation

        When individula bits of an object are used as Boolena values, the bits are called bit flags

        Given a sequencve of bits, we typically number the bits from right to left, starting with 0 (not 1)
        Each number denotes a bit position

        76543210  Bit position
        00000101  Bit sequence

        - test() allows us to query whether a bit is a 0 or 1.
        - set() allows us to turn a bit on (this will do nothing if the bit is already on).
        - reset() allows us to turn a bit off (this will do nothing if the bit is already off).
        - flip() allows us to flip a bit value from a 0 to a 1 or vice versa.

        Thus, a std::bitset<8> will typically use either 4 or 8 bytes of memory, even though it technically only needs 1 byte to store 8 bits.
        Thus, std::bitset is most useful when we desire convenience, not memory savings.

        size() returns the number of bits in the bitset.
        count() returns the number of bits in the bitset that are set to true.
        all() returns a Boolean indicating whether all bits are set to true.
        any() returns a Boolean indicating whether any bits are set to true.
        none() returns a Boolean indicating whether no bits are set to true.

    */
    std::bitset<8> mybitset{};        // 8 bits in size means room for 8 flags
    std::bitset<8> bits{0b0000'0101}; // we need 8 bits , start with bit pattern 0000 0101
    bits.set(3);                      // set bit position 3 to 1 (0000 1101)
    bits.flip(4);                     // flip bit 4 (0001 1101)
    bits.reset(4);                    //(0000 1101)

    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';

    std::bitset<8> bits_{0b0000'1101};
    std::cout << bits_.size() << " bits are in the bitset\n"; // 8 bits are in the bitset
    std::cout << bits_.count() << " bits are set to true\n";  // 3 bits are set to true

    std::cout << std::boolalpha;
    std::cout << "All bits are true: " << bits_.all() << '\n';  // All bits are true: false
    std::cout << "Some bits are true: " << bits_.any() << '\n'; // Some bits are true: true
    std::cout << "No bits are true: " << bits_.none() << '\n';  // No bits are true: false

    /*
    C++ provides 6 bit manipulation operators, often called bitwise operators

    left shift	<<	x << y	all bits in x shifted left y bits
    right shift	>>	x >> y	all bits in x shifted right y bits
    bitwise NOT	~	~x	all bits in x flipped
    bitwise AND	&	x & y	each bit in x AND each bit in y
    bitwise OR	|	x | y	each bit in x OR each bit in y
    bitwise XOR	^	x ^ y	each bit in x XOR each bit in y

    0011 << 1 is 0110
    0011 << 2 is 1100
    0011 << 3 is 1000

    1100 >> 1 is 0110
    1100 >> 2 is 0011
    1100 >> 3 is 0001
    */

    std::bitset<4> x{0b1101};
    std::cout << (x >> 1) << std::endl; // shift right by 1, yielding 0110

    unsigned int y{0b0100};
    y = y << 1;                             // use operator<< for left shift
    std::cout << std::bitset<4>{y} << '\n'; // use operator<< for output

    /*
        The bitwise NOT operator (~) is perhaps the easiest to understand of all the bitwise operators.
         It simply flips each bit from a 0 to a 1,
         Flipping 8 bits:
        ~0000 0100 is 1111 1011

    */
    std::cout << ~std::bitset<4>{0b0100} << ' ' << ~std::bitset<8>{0b0100} << '\n'; // 1011 11111011

    /*
     Bitwise OR (|) works much like its logical OR counterpart. However, instead of applying the OR to the operands to produce a single result,
     bitwise OR applies to each bit! For example, consider the expression 0b0101 | 0b0110.
    */

    std::cout << (std::bitset<4>{0b0101} | std::bitset<4>{0b0110}) << '\n';
    // 0 1 0 1 OR
    // 0 1 1 0
    //-------
    // 0 1 1 1

    /*
    Bitwise AND (&) works similarly to the above. Logical AND evaluates to true if both the left and right operand evaluate to true.
    Bitwise AND evaluates to true (1) if both bits in the column are 1. Consider the expression 0b0101 & 0b0110.
    Lining each of the bits up and applying an AND operation to each column of bits:
    0 1 0 1 AND
    0 1 1 0
    --------
    0 1 0 0
    */

    std::cout << (std::bitset<4>{0b0101} & std::bitset<4>{0b0110}) << '\n'; // 0100

    /*
    The last operator is the bitwise XOR (^), also known as exclusive or.

     When evaluating two operands, XOR evaluates to true (1) if one and only one of its operands is true (1).
     If neither or both are true, it evaluates to 0. Consider the expression 0b0110 ^ 0b0011:

     0 1 1 0 XOR
     0 0 1 1
     -------
     0 1 0 1
    */

    /*
      bitwise assignment operators
      Left shift assignment	<<=	x <<= y	Shift x left by y bits
      Right shift assignment	>>=	x >>= y	Shift x right by y bits
      Bitwise OR assignment	|=	x |= y	Assign x | y to x
      Bitwise AND assignment	&=	x &= y	Assign x & y to x
      Bitwise XOR assignment	^=	x ^= y	Assign x ^ y to x

      For example, instead of writing x = x >> 1;, you can write x >>= 1;
    */

    std::uint8_t c{0b00001111};

    std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c)) << '\n';     // correct: prints 00000000000000000000000011110000
    std::cout << std::bitset<32>(static_cast<std::uint8_t>(c << 6)) << '\n'; // correct: prints 0000000000000000000011000000
    std::uint8_t cneg{static_cast<std::uint8_t>(~c)};                        // compiles
    c = static_cast<std::uint8_t>(~c);                                       // no warning

    /*

    A bit mask is a predefined set of bits that is used to select which specific
    bits will be modified by subsequent operations.

    */

    constexpr std::uint8_t mask3{1 << 3}; // 0000 1000

    return 0;
}
