#include <iostream>

inline int min(int x, int y)
{ // inline keyword means this function is an inline function
     return (x < y) ? x : y;
}

void incrementAndPrint()
{
     static int s_value{1}; // static duration via static keyword
     // This initializer is only executed once
     ++s_value;
     std::cout << "Value after increment: " << s_value << std::endl;
     // s_value is NOT destoryed here, but bceomes inaccessible because it goes out of scope
     // This is because we made it static
}
// This can be down in foo.cpp
namespace Foo // define a namesapce Foo
{
     int doSomething(int x, int y)
     {
          return x + y;
     }

     namespace Bar
     {
          int add(int x, int y, int z)
          {
               return x + y + z;
          }
     }
}

namespace Goo // define a namespace named Goo
{
     // This doSomething() belongs to namespace Goo
     int doSomething(int x, int y)
     {
          return x - y;
     }
}

int main()
{

     /*

     A compound statement (also called a block or block statement)
     is a group of zero or more statements that is traeted by the compiler
     as if it were a single statement. I begins with a { and ends with a }

     Although funcitons cant be nested inside other functions,
     blocks can be nester inside other blocks

     When blocks are nested, the enclosing blocks is tpyically called the outer block
     and the enclosed blokc is called the inner block or nested block

     C++ allows us to define our own namespaces via the namespace keyword.
     namespaces that you create in your own programs are casually called
     user-defined namespace (though it would be more accurate to call them program-defined namespaces)

     namespace NameSpaceIdentifier
     {
          //content of namespace here
     }
     */

     std::cout << "Testing Foo's namespace: " << Foo::doSomething(1, 2) << '\n';
     std::cout << "Testing Goo's namespace: " << Goo::doSomething(1, 2) << '\n';
     std::cout << "Testing Bar's namespace: " << Foo::Bar::add(1, 2, 3) << '\n';

     /*
     local variables, are variables that are defiend inside a funciton

     Local variables have block scope
     local variables haveblock scope, which eans they are in scope frmo their point of
     defination to the end of the block they are defined within

     A variables storage duration (usually jsut called duration) determine
     what rules govern when and how a variable will be created (instantiated)
     and destroyed

     lcoal variables have automatic storage duration, which means they are
     created at the point of defination and destoryed at the end of the block
     they are defined in

     For this reason, local variables are sometimes called automatic variables

     Identifiers have another property named linkage. An identifier linkage determines
     whether a declaration of that same identifier in a different scope refers to the same object (or funciton)

     In C++, variables can also be declared outside of a funciton.
     Such variables are called global variables

     By convention, lgobal variaables are decalred at the top of a file

     Global araiables are craeted when the program starts
     (before main() begins execution), and destroyed when it ends.
     This is called static duration. Variables with static duration are
     someties called static variables

     When being a global variable, the constant variables must be initialized

     Each block defines its own scope region. So what happens when we have a variable
     inside a nested block that has the same name as a variable in an outer block?
     When this happens, the nested variable “hides” the outer variable in areas where they are both in scope.
      This is called name hiding or shadowing.

     int val {5};

     void foo(){

          print val // this prints out the 5, and hide the var in the main local
     }

     int main(){
          int val {10}
          print val // this will print 10 and hide the global

          --(::val) this will decrement the global var, but not the local
     }
     */

     /*

      An identifier with internal linkage can be seen and used within a single translation unit,
      but it is not accesible from other translation units.

      Static variable is a variable that has static storage duration,
      meaning it exisits for the entire lifetime of the program
      1) Local static variable (inside a funciton)
      2) Global static variable (outside a funciton)
      3) Static Class Member (the varible issahred among all objects of the class)

     all of the extra work that must happen to setup, facilitate, and/or cleanup
     after some task (in this case, making a function call) is called overhead.

     the c++ compiler has  trick that it can avoid such ovehead case
     ; Inline explansion is a process where a function call is replaced
     by the code from the called functions defination

     C++ provided the keyword inline, which was orignially intended to be used
     as a hint to thte computer that a function would benefit from being
     expanded inline

     A function that is declared using the inline keyword is called an inline function
     I wrote an inline function above at the top

     Best practice

     Do not use the inline keyword to request inline expansion for your functions.


     */

     /*
      Using the static keyword on a local variable changes its duration from automatic
      during to startic duration

      Look at incrementAndPrint above
     */

     incrementAndPrint();
     incrementAndPrint();
     incrementAndPrint();

     /*
     Variables with block (local) scope can only be accessed from the point of declaration until the end of the block in which they are declared
      (including nested blocks).

      Variables and functions with global scope can be accessed from the point of declaration until the end of the file. This includes:

      Using declarations and using directives

      A qualified name is a name that includes an associated scope. Most often, names are qualified with a namespace using the scope resolution operator (::)

      An unqualified name is a name that does not include a scoping qualifier. For example, cout and x are unqualified names, as they do not include an associated scope.

       A using declaration allows us to use an unqualified name (with no scope) as an alias for a qualified name.

       In C++, unconditional jumps are implemented via a goto statement, and the spot to jump to is identified through use of a statement label.
       Just like with switch case labels, statement labels are conventionally not indented.
     */

     double p{0};
tryAgain:
     std::cout << "Current Num: " << p << '\n';
     p++;
     if (p < 5)
     {
          goto tryAgain; // this is the go to statement
     }

     // std::exit(0);

     return 0;
}
