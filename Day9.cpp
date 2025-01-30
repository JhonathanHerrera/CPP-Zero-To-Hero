#include <iostream>
#include <string>
#include <string_view>

struct Employee
{
	int id{};
	int age{};
	double wage{};
};

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream &operator<<(std::ostream &out, Color_ color)
{
	out << getColorName(color); // print our color's name to whatever output stream out
	return out;					// operator<< conventionally returns its left operand

	// The above can be condensed to the following single line:
	// return out << getColorName(color)
}

std::ostream &operator<<(std::ostream &out, const Employee &e)
{
	out << e.id << ' ' << e.age << ' ' << e.wage;
	return out;
}
struct Fraction
{
	int numerator{};
	int denominator{};
};

// Mid solution
using Color = int; // define a type alias named Color

// The following color values should be used for a Color
constexpr Color red{0};
constexpr Color green{1};
constexpr Color blue{2};

enum Color_
{
	// Here are the enumerators
	// These symbolic constants define all the possible values this type can hold
	// Each enumerator is separated by a comma, not a semicolon
	red_,
	green_,
	blue_, // trailing comma optional but recommended
	black_,
};

enum Animal
{
	cat = -3, // -3
	dog,	  // -2
	pig,	  // -1
	// note: no enumerator with value 0 in this list
	horse = 5,	 // 5
	giraffe = 5, // 5
	chicken,	 // 6
};

constexpr std::string_view getColorName(Color_ color)
{
	switch (color)
	{
	case black_:
		return "black";
	case red_:
		return "red";
	case blue_:
		return "blue";
	default:
		return "???";
	}
}

enum Pet
{
	cat,   // 0
	dog,   // 1
	pig,   // 2
	whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
	switch (pet)
	{
	case cat:
		return "cat";
	case dog:
		return "dog";
	case pig:
		return "pig";
	case whale:
		return "whale";
	default:
		return "???";
	}
}
int main()
{

	/*
	Introduction to program-desfined (user defined) types

	Instead, C++ solves such problems in a different way: by allowing us to create entirely new, custom types for use in our programs!
	Such types are often called user-defined types (though we think the term program-defined types is better -- we’ll discuss the difference later in this lesson).

	C++ has two different categories of compound types that can be used to create program-defined types:

	Enumerated types (including unscoped and scoped enumerations)
	Class types (including structs, classes, and unions).
	*/
	Fraction f{3, 4};

	/*
	In this example, we’re using the struct keyword to define a new program-defined type named Fraction (in the global scope, so it can be used anywhere in the rest of the file).
	This doesn’t allocate any memory -- it just tells the compiler what a Fraction looks like, so we can allocate objects of a Fraction type later. Then, inside main(), we instantiate (and initialize) a variable of type Fraction named f.
	*/

	/*
	Unscoped enumerations
	*/
	Color appleColor{red};
	Color shirtColor{green};
	// mid

	/*
	Enumerations:
	An enumeration (also called an enumerated type or an enum) is a compound data type whose values are restricted to a set of named symbolic constants (called enumerators).
	*/
	Color_ apple{red_};
	Color_ shirt{green_};
	Color_ cup{blue_};

	/*
	Converting an enumeartion to and from a string

	Color shirt{ blue };

	std::cout << "Your shirt is " << shirt << '\n';

	This prints:

	Your shirt is 2

	How to fix this
	*/

	constexpr Color_ shirt{blue_};
	std::cout << "Your shirt is " << getColorName(shirt) << '\n';

	std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

	int input{3};
	// std::cin >> input; // input an integer

	if (input < 0 || input > 3)
		std::cout << "You entered an invalid pet\n";
	else
	{
		Pet pet{static_cast<Pet>(input)}; // static_cast our integer to a Pet
		std::cout << "You entered: " << getPetName(pet) << '\n';
	}

	/*
	Introduciton to overloading the I/O operators

	*/

	Color_ shirt{blue_};
	std::cout << "Your shirt is " << shirt << '\n'; // it works!

	/*
	Introduction to structs, members, and member selection
	*/
	Employee joe{};
	joe.age = 32;

	std::cout << joe.age << '\n';

	/*
	Struct aggregate initialization
	*/
	Employee joe{2, 28, 45000.0}; // list initialization using braced list (preferred)
	std::cout << joe << '\n';

	return 0;
}
