#include<iostream>

// !! Declarations and definitions (C++)

A C++ program consists of various entities such as variables, functions, types, and namespaces. Each of these entities must be 
declared before they can be used.A declaration specifies a unique name for the entity, along with information about its type and 
other characteristics.In C++ the point at which a name is declared is the point at which it becomes visible to the compiler。
You can't refer to a function or class that is declared at some later point in the compilation unit。Variables should be declared 
as close as possible before the point at which they're used.


#include <string>

int f(int i); // forward declaration

int main()
{
    const double pi = 3.14; //OK
    int i = f(2); //OK. f is forward-declared
    // The name std::string is visible because it's introduced in the string header file, 
    // which is merged into the source file in line 1. std is the namespace in which the string class is declared.
    std::string str;
    C obj; // error! C not yet declared.
    j = 0; // error! No type specified.
    auto k = 0; // OK. type inferred as int by compiler.
}

int f(int i)
{
    return i + 42;
}

namespace N {
   class C{/*...*/};
}


// !! Definitions

Some entities, including functions, classes, enums, and constant variables, must be defined as well as declared. A definition provides
the compiler with all the information it needs to generate machine code when the entity is used later in the program.

A constant variable must be defined, in other words assigned a value, in the same statement in which it's declared.

A declaration of a built-in type such as int is automatically a definition because the compiler knows how much space to allocate for it.


// !! The following example shows declarations that are also definitions:
// Declare and define int variables i and j.
int i;
int j = 10;

// Declare enumeration suits.
enum suits { Spades = 1, Clubs, Hearts, Diamonds };

// Declare class CheckBox.
class CheckBox : public Control
{
public:
    Boolean IsChecked();
    virtual int     ChangeState() = 0;
};

// !! Here are some declarations that aren't definitions:

extern int i;
char *strchr( const char *Str, const char Target );



// !! Typedefs and using statements

In older versions of C++, the typedef keyword is used to declare a new name that is an alias for another name. For example, 
the type std::string is another name for std::basic_string<char>. It should be obvious why programmers use the typedef name
and not the actual name. In modern C++, the using keyword is preferred over typedef, but the idea is the same: a new name is 
declared for an entity, which is already declared and defined.(在现代 c + + 中， using 关键字优先于 typedef，但思路相同：为已声明和定义的
实体声明了新名称)

// !! Static class members


Because static class data members are discrete variables that are shared by all objects of the class, they must be defined and 
initialized outside the class definition. 


// !! extern declarations

A C++ program might contain more than one compilation unit. To declare an entity that is defined in a separate compilation unit, 
use the extern keyword. The information in the declaration is sufficient for the compiler, but if the definition of the entity 
can't be found in the linking step, then the linker will raise an error.


int main(int argc, char **argv)
{

}