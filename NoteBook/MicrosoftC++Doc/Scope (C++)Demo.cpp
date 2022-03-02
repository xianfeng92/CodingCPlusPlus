#include <iostream>


// !! Scope (C++)

When you declare a program element such as a class, function, or variable, its name can only be "seen" and used in certain parts 
of your program. The context in which a name is visible is called its scope. For example, if you declare a variable x within a function,
x is only visible within that function body. It has local scope. You may have other variables by the same name in your program; as long 
as they are in different scopes, they do not violate the One Definition Rule and no error is raised.

For automatic non-static variables, scope also determines when they are created and destroyed in program memory.

There are six kinds of scope:

1. Global scope
    
   A global name is one that is declared outside of any class, function, or namespace.However, in C++ even these names exist with an 
   implicit global namespace. The scope of global names extends from the point of declaration to the end of the file in which they 
   are declared. For global names, visibility is also governed by the rules of linkage which determine whether the name is visible 
   in other files in the program.

2. Namespace scope

  A name that is declared within a namespace, outside of any class or enum definition or function block, is visible from its point 
  of declaration to the end of the namespace. A namespace may be defined in multiple blocks across different files.

3. Local scope

  A name declared within a function or lambda, including the parameter names, have local scope,Local scope is a kind of block scope

4. Class scope

   Names of class members have class scope, which extends throughout the class definition regardless of the point of declaration.  
   Class member accessibility is further controlled by the public, private, and protected keywords. Public or protected members can 
   be accessed only by using the member-selection operators (. or ->) or pointer-to-member operators (.* or ->*).

5. Statement scope

   Names declared in a for, if, while, or switch statement are visible until the end of the statement block.

6. Function scope

   A label has function scope, which means it is visible throughout a function body even before its point of declaration.


// !! Hiding Names

You can hide a name by declaring it in an enclosed block. In the following figure, i is redeclared within the inner block, thereby 
hiding the variable associated with i in the outer block scope.


// !! Hiding names with global scope

You can hide names with global scope by explicitly declaring the same name in block scope. However, global-scope names can be accessed
using the scope-resolution operator (::).

#include <iostream>

int i = 7;   // i has global scope, outside all blocks
using namespace std;

int main( int argc, char *argv[] )
{
   int i = 5;   // i has block scope, hides i at global scope
   cout << "Block-scoped i has the value: " << i << "\n";
   cout << "Global-scoped i has the value: " << ::i << "\n";
}







int main(int argc, char **argv)
{

}