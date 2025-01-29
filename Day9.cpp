#include <iostream>

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
	unscoped enumeators integral conversions


	*/

	return 0;
}
