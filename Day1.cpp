#include <iostream>

int main()
{
    int x;
    double width;
    width = 5;
    int inches{72};
    int a = 5, b = 6; // copy-initialization
    int c(7), d(8);   // direct-initialization
    int e{9}, f{10};  // direct-list-initialization
    int i{}, j{};     // value-initialization
    [[maybe_unused]] double pi{3.14};
    std::cout << "Hello World!";
    std::cout << width;
    std::cout << inches;

    return 0;
}