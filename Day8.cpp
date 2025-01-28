#include <iostream>
#include <string>
#include <optional>

void printValue(std::string &y) // YAHHHH // y only accepts modifiable lvalues
{
	std::cout << y << '\n';
}

void printValue_bad(std::string y) // NOO
{
	std::cout << y << '\n';
}

void printAddresses(int val, int &ref)
{
	std::cout << "The address of the value parameter is: " << &val << '\n';
	std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

void printByValue(std::string val) // The function parameter is a copy of str
{
	std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string &ref) // The function parameter is a reference that binds to str
{
	std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string *ptr) // The function parameter is a pointer that holds the address of str
{
	std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

// Pass by address for "optional" argument
void printIDNumber(const int *id = nullptr)
{
	if (id)
		std::cout << "Your ID number is " << *id << ".\n";
	else
		std::cout << "Your ID number is not known.\n";
}

const std::string &getProgramName() // returns a const reference
{
	static const std::string s_programName{"Calculator"}; // has static duration, destroyed at end of program

	return s_programName;
}

const int &getNextId()
{
	static int s_x{0}; // note: variable is non-const
	++s_x;			   // generate the next id
	return s_x;		   // and return a reference to it
}

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
	if (y == 0)
		return {}; // or return std::nullopt
	return x / y;
}
int main()
{

	/*
	Two types of reference
	1) Lvalue
	2) Rvalue

	An lvalue reference variable is a variable that acts as a reference to an lvalue (usually another variable).

	*/
	int x{5};	 // normal integer variable
	int &ref{x}; // ref is now an alias for variable x

	std::cout << x << ref << '\n'; // print 55

	x = 6; // x now has value 6

	std::cout << x << ref << '\n'; // prints 66

	ref = 7; // the object being referenced (x) now has value 7

	std::cout << x << ref << '\n'; // prints 77

	/*
	References cant be reseated (changed to rfer to another object)

	When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists.
	Such a reference is called a dangling reference. Accessing a dangling reference leads to undefined behavior.

	References aren’t objects:
	In cases where you need a reference that is an object or a reference that can be reseated, std::reference_wrapper


	*/
	int x{1};
	int &ref{x};

	std::cout << x << ref << '\n';

	int y{2};
	ref = y;
	y = 3;

	std::cout << x << ref << '\n';

	x = 4;

	std::cout << x << ref << '\n';
	// 11 22 44
	// Because ref is bound to x, x and ref are synonymous, so they will always print the same value. The line ref = y assigns the value of y (2) to ref -- it does not change ref to reference y. The subsequent line y = 3 only changes y.

	/*
	Lvalue reference can only bind to modifiablke lvalue, meaning that this is illegal
	const int x{5};
	int& ref {x} //error ref can not be bind to non modifiable lvalue

	By using the const keyword when declaring an lvalue reference, we tell an lvalue reference to treat the object it is referencing as const. Such a reference is called an lvalue reference to a const value (sometimes called a reference to const or a const reference).

	const int x { 5 };    // x is a non-modifiable lvalue
	const int& ref { x }; // okay: ref is a an lvalue reference to a const value

	int x { 5 };          // x is a modifiable lvalue
	const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

	Pass by lvalue reference
	int x { 2 };

	printValue(x); // x is passed by value (copied) into parameter y (inexpensive)
	In the above program, when printValue(x) is called, the value of x (2) is copied into parameter y. Then, at the end of the function, object y is destroyed

	Some objects are expensive to copy
	Most of the types provided by the standard library (such as std::string) are class types. Class types are usually expensive to copy.

	Whenever possible, we want to avoid making unnecessary copies of objects that are expensive to copy, especially when we will destroy those copies almost immediately.
	void printValue(std::string y)
	{
		std::cout << y << '\n';
	} //y is destroyed here
	std::string x { "Hello, world!" }; // x is a std::string

	printValue(x); // x is passed by value (copied) into parameter y (expensive)

	One way to avoid making an expensive copy of an argument when calling a function is to use pass by reference instead of pass by value.
	When using pass by reference, we declare a function parameter as a reference type (or const reference type) rather than as a normal type. When the function is called, each reference parameter is bound to the appropriate argument.
	Because the reference acts as an alias for the argument, no copy of the argument is made



	*/

	int x{5};
	std::cout << "The address of x is: " << &x << '\n';
	printAddresses(x, x);
	/*
	The address of x is: 0x7ffd16574de0
	The address of the value parameter is: 0x7ffd16574de4
	The address of the reference parameter is: 0x7ffd16574de0

	We can see that the argument has a different address than the value parameter, meaning the value parameter is a different object.
	Since they have separate memory addresses, in order for the value parameter to have the same value as the argument, the argument’s value must be copied into memory held by the value parameter.
	*/

	/*
	int x {5};
	if you have a function like addOne(x)
	while it looks like this
	void addOne(int y){++y} this modifies the copy of x, not the actual object x

	void printValue(int& y) // y only accepts modifiable lvalues
	{
		std::cout << y << '\n';
	}

	int x { 5 };
	printValue(x); // ok: x is a modifiable lvalue

	const int z { 5 };
	printValue(z); // error: z is a non-modifiable lvalue

	printValue(5); // error: 5 is an rvalue
	*/

	/*
	INTRODUCTION TO POINTERS
	char x{}; //chars use 1 byte of memory

	Although the memory addresses used by variables aren’t exposed to us by default, we do have access to this information.
	The address-of operator (&) returns the memory address of its operand. This is pretty straightforward:

	The most useful thing we can do with an address is access the value stored at that address. The dereference operator (*) (also occasionally called the indirection operator)
	returns the value at a given memory address as an lvalue:

	int x{ 5 };
	std::cout << x << '\n';  // print the value of variable x
	std::cout << &x << '\n'; // print the memory address of variable x

	std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

	A pointer is an object that holds a memory address (typically of another variable) as its value. This allows us to store the address of some other object to use later.

	int;  // a normal int
	int&; // an lvalue reference to an int value
	int*; // a pointer to an int value (holds the address of an integer value)

	int x { 5 };    // normal variable
	int& ref { x }; // a reference to an integer (bound to x)

	int* ptr;       // a pointer to an integer


	int* ptr;        // an uninitialized pointer (holds a garbage address)
	int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
	int* ptr3{ &x }; // a pointer initialized with the address of variable x
	*/

	int x{5};
	int *ptr{&x}; // ptr initialized to point at x

	std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

	int y{6};
	ptr = &y; // // change ptr to point at y

	std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)

	/*
	Null Pointers

	Besides a memory address, there is one additional value that a pointer can hold: a null value. A null value (often shortened to null) is a special value that means something has no value.
	When a pointer is holding a null value, it means the pointer is not pointing at anything. Such a pointer is called a null pointer

	int* ptr {}; -> a null pointer

	int x { 5 };
	ptr = &x; // ptr now pointing at object x (no longer a null pointer)

	int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer

	Dereferencing a null pointer results in undefined behavior

	Pointer and const

	const int x { 5 }; // x is now const
	int* ptr { &x };   // compile error: cannot convert from const int* to int*

	A pointer to a const value (sometimes called a pointer to const for short) is a (non-const) pointer that points to a constant value.

	const int x{ 5 };
	const int* ptr { &x }; // okay: ptr is pointing to a "const int"

	*ptr = 6; // not allowed: we can't change a const value

	However, because a pointer to const is not const itself (it just points to a const value), we can change what the pointer is pointing at by assigning the pointer a new address:
	const int y{ 6 };
	ptr = &y; // okay: ptr now points at const int y

	A const pointer is a pointer whose address can not be changed after initialization.

	int* const ptr { &x }; // const after the asterisk means this is a const pointer

	int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
	ptr = &y; // error: once initialized, a const pointer can not be changed.

	Pass by Address
	With pass by address, instead of providing an object as an argument, the caller provides an object’s address (via a pointer).
	This pointer (holding the address of the object) is copied into a pointer parameter of the called function (which now also holds the address of the object). The function can then dereference that pointer to access the object whose address was passed.
	*/

	std::string str{"Test"};
	std::string str2{"Test2"};

	printByValue(str);
	printByReference(str);
	printByAddress(&str);

	std::string *str_pointer{&str2};
	printByAddress(str_pointer);

	/*
	If printByAdress had the parameters of (const int* ptr) then the function paramter is a
	pointer that holds the address of the argument

	if you call this function like this printByAddress(&5) itll be an error because it cant
	take the address of a r-value
	*/

	/*
	Return by reference and return by address

	Return by reference returns a reference that is bound to the object being returned, which avoids making a copy of the return value.\

	std::string& returnByReference(); // returns a reference to an existing std::string (cheap)
	const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)


	*/
	std::cout << "This program is named " << getProgramName() << '\n';
	// if you dont have the static by the programName, then now its a non-static local variable, and
	// destroyed when the function ends

	const int &id1{getNextId()}; // id1 is a reference
	const int &id2{getNextId()}; // id2 is a reference

	std::cout << id1 << id2 << '\n';

	/*
	In and out parameters

	In most cases, a function parameter is used only to receive an input from the caller. Parameters that are used only for receiving input from the caller are sometimes called in parameters.

	A function parameter that is used only for the purpose of returning information back to the caller is called an out parameter.

	In rare cases, a function will actually use the value of an out-parameter before overwriting its value. Such a parameter is called an in-out parameter. In-out-parameters work identically to out-parameters and have all the same challenges.


	*/

	/*
	Type deduction with pointers, references, and const

		std::string& getRef(); // some function that returns a reference

		auto ref1 { getRef() };  // std::string (reference dropped)
		auto& ref2 { getRef() }; // std::string& (reference dropped, reference reapplied)
	*/

	// Optional
	std::optional<int> result1{doIntDivision(20, 5)};
	if (result1)									   // if the function returned a value
		std::cout << "Result 1: " << *result1 << '\n'; // get the value
	else
		std::cout << "Result 1: failed\n";

	return 0;
}
