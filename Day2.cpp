#include <iostream>
#include <cstdlib>
using namespace std;

#define MY_NAME "Jhonathan"
#define PRINT_JOE

// Header Guards
// Can be used in the header file like this
#ifndef SQUARE
#define SQUARE

// More Modern compliler support
// Not usually in main files -> instead in header files
// #pragma once

int getSquareSides()
{
    return 4;
}

#endif

/*
Avoid using-directives (such as using namespace std;)
 at the top of your program or in header files.
 They violate the reason why namespaces were added in the first place.
*/

// Use Forward Deeclaration
int add(int x, int y);

int main()
{

    int x{5};

    std::cout << x << '\n';

    [[maybe_unused]] int y{};

    // std::cin >> y;

    // std::cout << y;

    std::cout << sizeof(int) << '\n';

    int z{4};

    std::cout << (z = 2) << '\n';

    // Start of Chapter 2
    /*
        The C++ standard only defines the meaning of 3 status codes:
        0, EXIT_SUCCESS, and EXIT_FAILURE. 0 and
         EXIT_SUCCESS both mean the program executed successfully.
         EXIT_FAILURE means the program did not execute successfully.
    */

    std::cout << "Foward: " << add(4, 3) << '\n';

    std::cout << "My name is " << MY_NAME << std::endl;

#ifdef PRINT_JOE
    std::cout << "Joe is a great programmer!" << std::endl;
#endif

    // Lets say that we have another file called Alex.h
    // we Can have #define MY_NAME "Alex" in that file and in this Day2.cpp we can do #define "Alex.h"
    // That will still work and count for Day2.cpp if we want to use it

    // End of Chapter 2
    return EXIT_SUCCESS;
}

int add(int x, int y)
{
    return x + y;
}