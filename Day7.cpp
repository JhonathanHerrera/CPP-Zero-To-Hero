#include <iostream>
#include <limits>	   // for std::numeric_limits
#include <cassert>	   // for assert()
#include <type_traits> // for std:::common_type_t

// For more advanced readers
template <typename T, typename U>
auto greatType(T x, U y) -> std::common_type_t<T, U>; // returns the common type of T and U
// What does common_type_t do?
/*
std::common_type_t figures out the "best common type" that can hold values of two or more types
without losing information
"If i mix two or more types, what type can represent all of them safely?"
*/
void printInt(int x)
{
	std::cout << "int: " << x << '\n';
}

void printIntOnly(int y)
{
	std::cout << "int only: " << y << '\n';
}

void printDefaultParamter(int z = 12)
{
	std::cout << "default parameter: " << z << '\n';
}

// This fuction template will take precendence for arguments of other types
// since this function template is deleted, calls to it will halt compilation
template <typename T>
void printIntOnly(T y) = delete;

template <typename T>
T max(T x, T y)
{
	return (x > y) ? x : y;
}

template <typename T, typename U>
T maxWithDifferentTypes(T x, U y)
{
	return (x > y) ? x : y;
}

int main()
{

	/*
	This call would remove up to 100 characters, but if the user entered more than 100 characters we’ll get messy output again.
	To ignore all characters up to the next ‘\n’, we can pass std::numeric_limits<std::streamsize>::max() to std::cin.ignore().
	std::numeric_limits<std::streamsize>::max() returns the largest value that can be stored in a variable of type std::streamsize.
	 Passing this value to std::cin.ignore() causes it to disable the count check.

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	In programming, a precondition is any condition that must be true prior to the execution of some section of code (typically the body of a function).

	Similarly, a postcondition is something that must be true after the execution of some section of code.

	An assertion is an expression that will be true unless there is a bug in the program.
	If the expression evaluates to true, the assertion statement does nothing. If the conditional expression evaluates to false,
	an error message is displayed and the program is terminated (via std::abort).
	*/

	double gravity{1.0};
	int car{1};
	assert(gravity > 0.0);
	// assert(car > 2 && "Not enough cars broke boy"); This fails

	/*
	The process of producing a new value of some type from a value of a different type is called a conversion.
	Implicit type conversion (also called automatic type conversion or coercion) is performed automatically by the compiler when one data type is required,
	but a different data type is supplied.

	 A numeric promotion is the type conversion of certain narrower numeric types (such as a char) to certain wider numeric types (typically int or double) that can be processed efficiently.
	*/

	using Distance = double; // define Distance as an alias for type double

	Distance milesToDestination{3.4}; // defines a variable of type double

	/*
	Function Overloading and Function Template

	 Function overloading allows us to create multiple functions with the same name,
	 so long as each identically named function has different parameter types (or the functions can be otherwise differentiated).
	 Each function sharing a name (in the same scope) is called an overloaded function (sometimes called an overload for short).

	 int add(int x, int y) // integer version
	{
		return x + y;
	}

	double add(double x, double y) // floating point version
	{
		return x + y;
	}

	In c++, typedef is used to craete an alias for an existing data type. it allows you to
	define a new name for a type

	format:
	typedef existing_data_type new_data_type; //typedef
	using new_data_type = existing_data_type; //type alias
	typedef int Height; // typedef
	using Age = int; // type alias

	The process of matching function calls to a specific overloaded function is called overload resolution.

	*/

	printInt(5);
	printInt('a');
	printInt(true);

	/*
	Deleting a function using the = delete specifier

	in cases where we have a functiopn that we explicityl do not want to be callable,
	we can define that function as deleted by using the = delete specifier.

	So if we do
	void printInt(char) = delete; //calls to this funciton will halt compilation
	void printInt(bool) = delete; //calls to this funciton will halt compilation

	What does halt compilation mean?
	refers to a situation where the compiler stops processing the source code because it encounters an error
	or a directrive that expicitly instructs it to stop

	Deleting a bunch of indiivdual functions overloads works fine, but can be verbose. there may be times when
	we want a certain function to be called onbly iwth arguments whose types exactly match the funciton paramter.
	we can do this by using a function template


	*/

	printIntOnly(23); // This is ok
	// printIntOnly(true); This will cause a compile error

	printDefaultParamter(); // we dont need to pass anything in, since we have a default

	/*
	Function template
	Instead of manually creating a bunch of mostly-identical functions or classes (one for each set of different types),
	 we instead create a single template. Just like a normal definition, a template definition describes what a function or class looks like

	 A function template is a function-like definition that is used to generate one or more overloaded functions, each with a different set of actual types.
	  This is what will allow us to create functions that can work with many different types. The initial function template that is used to generate other
	  functions is called the primary template, and the functions generated from the primary template are called specializations.
	*/

	// To use the max as an int, we can makea function call with this syntax
	// the primary difference is the addition of the type in angled brackets(called a template argument)
	// You dont alwasy have to tho
	std::cout << "The max is: " << max<double>(4, 5.0) << '\n';
	std::cout << "The max is: " << max(4, 8) << '\n';

	/*
	template <typename T>
	doubleT max(T x, T y)
	{
		std::cout << "called max<int>(int, int)\n";
		return (x < y) ? y : x;
	}

	int max(int x, int y)
	{
		std::cout << "called max(int, int)\n";
		return (x < y) ? y : x;
	}

	int main()
	{
		std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
		std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
		std::cout << max(1, 2) << '\n';      // calls max(int, int)

		return 0;
	}
	*/

	/*
	Function templates with multiple templates types

	If you need to have something the same data type, you can do something like this, depending on the case
	std::cout << max(static_cast<double>(2), 3.5) << '\n';

	Or another way to deal with two different data types parameter is doing double typename like this
	template <typename T, typename U>
	*/

	std::cout << "Two template: " << maxWithDifferentTypes(2, 2.5) << '\n';

	// Common_type_t example
	using CommonType = std::common_type_t<int, double>;
	static_assert(std::is_same_v<CommonType, double>);
	std::cout << "int + double = double" << '\n';

	// what is is_same_v?
	// std::is_same_v is a shorthand for determining whether two types are the same. It returns true of false

	return 0;
}
