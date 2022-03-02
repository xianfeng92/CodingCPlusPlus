#include<iostream>

// !! Translation units and linkage



In a C++ program, a symbol,for example a variable or function name, can be declared any number of times within its scope. However, 
it can only be defined once. This rule is the "One Definition Rule" (ODR).

A declaration introduces (or reintroduces) a name into the program, along with enough information to later associate the name with 
a definition.

A definition introduces a name and provides all the information needed to create it.If the name represents a variable, a definition 
explicitly creates storage and initializes it. A function definition consists of the signature plus the function body. A class 
definition consists of the class name followed by a block that lists all the class members. (The bodies of member functions may 
optionally be defined separately in another file.)


The following example shows some declarations:

int i;
int f(int x);
class C;

The following example shows some definitions:

int i{42};
int f(int x)
{
  return x * i;
}
class C 
{
public:
   void DoSomething();
};


A program consists of one or more translation units. A translation unit consists of an implementation file and all the headers that 
it includes directly or indirectly. Implementation files typically have a file extension of .cpp or .cxx. Header files typically have
an extension of .h or .hpp. Each translation unit is compiled independently by the compiler. After the compilation is complete, the 
linker merges the compiled translation units into a single program. 

Violations of the ODR rule typically show up as linker errors. Linker errors occur when the same name has two different definitions 
in different translation units.

In general, the best way to make a variable visible across multiple files is to put it in a header file. Then add an #include directive 
in every .cpp file that requires the declaration. By adding include guards around the header contents, you ensure that the names it 
declares are only defined once.



// !! External vs. internal linkage


A free function is a function that is defined at global or namespace scope. Non-const global variables and free functions by default 
have external linkage; they're visible from any translation unit in the program. No other global object can have that name. A symbol 
with internal linkage or no linkage is visible only within the translation unit in which it's declared. When a name has internal 
linkage, the same name may exist in another translation unit. Variables declared within class definitions or function bodies have 
no linkage.

You can force a global name to have internal linkage by explicitly declaring it as static. This keyword limits its visibility to the 
same translation unit in which it's declared. In this context, static means something different than when applied to local variables.

The following objects have internal linkage by default:

1. const objects
2. constexpr objects
3. typedef objects
4. static objects in namespace scope

To give a const object external linkage, declare it as extern and assign it a value:

extern const int value = 42;



int main(int argc, char **argv)
{

}