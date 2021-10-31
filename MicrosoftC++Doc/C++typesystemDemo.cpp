#include<iostream>


// !! C++ type system

The concept of type is very important in C++. Every variable, function argument, and function return value must have a type in order 
to be compiled. Also, every expression (including literal values) is implicitly given a type by the compiler before it is evaluated. 
Some examples of types include int to store integer values, double to store floating-point values.or the Standard Library class 
std::basic_string to store text.You can create your own type by defining a class or struct.

The type specifies the amount of memory that will be allocated for the variable (or expression result)、 the kinds of values that may 
be stored in that variable、how those values (as bit patterns) are interpreted、and the operations that can be performed on it


// !! Specifying variable and function types

C++ is a strongly typed language and it is also statically-typed. every object has a type and that type never changes (not to be 
confused with static data objects). When you declare a variable in your code, you must either specify its type explicitly, or use 
the auto keyword to instruct the compiler to deduce(推断)the type from the initializer. When you declare a function in your code, you 
must specify the type of each argument and its return value, or void if no value is returned by the function.


After you first declare a variable, you cannot change its type at some later point. However, you can copy the variable’s value or 
a function’s return value into another variable of a different type.Such operations are called type conversions, which are sometimes 
necessary but are also potential sources of data loss or incorrectness.

When you declare a variable of POD (plain old data)type, we strongly recommend you initialize it, which means to give it an initial 
value. Until you initialize a variable, it has a "garbage" value that consists of whatever bits happened to be in that memory location 
previously. This is an important aspect of C++ to remember, especially if you are coming from another language that handles initialization 
for you. When declaring a variable of non-POD class type, the constructor handles initialization.


The following example shows some simple variable declarations with some descriptions for each.

int result = 0;              // Declare and initialize an integer.
double coefficient = 10.8;   // Declare and initialize a floating point value.
auto name = "Lady G.";       // Declare a variable and let compiler deduce the type.
auto address;                // error. Compiler cannot deduce a type without an intializing value.
age = 12;                    // error. Variable declaration must specify a type or use auto!
result = "Kenny G.";         // error. Can’t assign text to an int.
string result = "zero";      // error. Can’t redefine a variable with new type.
int maxValue;                // Not recommended! maxValue contains garbage bits until it is initialized.


// !! Fundamental (built-in) types


Unlike some languages, C++ has no universal base type from which all other types are derived. The language includes many fundamental 
types, also known as built-in types.This includes numeric types such as int, double, long, bool, plus the char and wchar_t types for 
ASCII and UNICODE characters. Most integral fundamental types (except bool, double, wchar_t, and related types) all have unsigned 
versions, which modify the range of values that the variable can store. 


For example, an int, which stores a 32-bit signed integer, can represent a value from -2,147,483,648 to 2,147,483,647. An unsigned 
int, which is also stored as 32-bits, can store a value from 0 to 4,294,967,295. The total number of possible values in each case 
is the same; only the range is different.

The fundamental types are recognized by the compiler, which has built-in rules that govern what operations you can perform on them, 
and how they can be converted to other fundamental types. 

Type	Size	Comment
int	    4 bytes	The default choice for integral values.
double	8 bytes	The default choice for floating point values.
bool	1 byte	Represents values that can be either true or false.
char	1 byte	Use for ASCII characters in older C-style strings or std::string objects that will never have to be converted to 
        UNICODE.

unsigned int 4 bytes Default choice for bit flags.        

long long 8 bytes Represents very large integer values.


// !! The void type

The void type is a special type; you cannot declare a variable of type void, but you can declare a variable of type void * 
(pointer to void), which is sometimes necessary when allocating raw (un-typed) memory. However, pointers to void are not 
type-safe and generally their use is strongly discouraged in modern C++. In a function declaration, a void return value 
means that the function does not return a value; this is a common and acceptable use of void. While the C language required 
functions that have zero parameters to declare void in the parameter list, for example, fou(void), this practice is discouraged 
in modern C++ and should be declared fou(). 


// !! const type qualifier

Any built-in or user-defined type may be qualified by the const keyword. Additionally, member functions may be const-qualified and
even const-overloaded. The value of a const type cannot be modified after it is initialized.

const double PI = 3.1415;
PI = .75 //Error. Cannot modify const variable.

The const qualifier is used extensively in function and variable declarations and "const correctness" is an important concept in C++; 
essentially it means to use const to guarantee, at compile time, that values are not modified unintentionally.

You can use the C++ const_cast operator on those rare occasions when you must remove const-ness from a variable.


// !! String types

Strictly speaking, the C++ language has no built-in string type; char and wchar_t store single characters - you must declare an array 
of these types to approximate a string, adding a terminating null value (for example, ASCII '\0')  to the array element one past the 
last valid character (also called a C-style string). C-style strings required much more code to be written or the use of external 
string utility library functions. But in modern C++, we have the Standard Library types std::string (for 8-bit char-type character 
strings) or std::wstring (for 16-bit wchar_t-type character strings). These C++ Standard Library containers can be thought of as 
native string types because they are part of the standard libraries that are included in any conformant C++ build environment.

The use of null-terminated character arrays (the C-style strings previously mentioned) is strongly discouraged in modern C++.


// !! User-defined types

When you define a class, struct, union, or enum, that construct is used in the rest of your code as if it were a fundamental type. 
It has a known size in memory, and certain rules about how it can be used apply to it for compile-time checking and, at runtime, 
for the life of your program. The primary differences between the fundamental built-in types and user-defined types are as follows:

1. The compiler has no built-in knowledge of a user-defined type. It learns of the type when it first encounters the definition 
   during the compilation process(编译过程).

2. You specify what operations can be performed on your type, and how it can be converted to other types, by defining 
(through overloading) the appropriate operators


// !! Pointer types

Dating back to the earliest versions of the C language, C++ continues to let you declare a variable of a pointer type by using the 
special declarator * (asterisk). A pointer type stores the address of the location in memory where the actual data value is stored.

In modern C++, these are referred to as raw pointers, and are accessed in your code through special operators * (asterisk) or -> 
(dash with greater-than). Working with pointer types has long been one of the most challenging and confusing aspects of C and C++ 
program development.

The first thing that you should know is declaring a raw pointer variable will allocate only the memory that is required to store an 
address of the memory location that the pointer will be referring to when it is dereferenced.Allocation of the memory for the data value 
itself (also called backing store) is not yet allocated. In other words, by declaring a raw pointer variable, you are creating a memory 
address variable, not an actual data variable.Dereferencing a pointer variable before making sure that it contains a valid address to a 
backing store will cause undefined behavior (usually a fatal error) in your program. 

int* pNumber;       // Declare a pointer-to-int variable.
*pNumber = 10;      // error. Although this may compile, it is a serious error. We are dereferencing an
                    // uninitialized pointer variable with no allocated memory to point to.

The example dereferences a pointer type without having any memory allocated to store the actual integer data or a valid memory address 
assigned to it. The following code corrects these errors:

int number = 10;          // Declare and initialize a local integer variable for data backing store.
int* pNumber = &number;   // Declare and initialize a local integer
                          // pointer variable to a valid memory address to that backing store.
...
    *pNumber = 41;            // Dereference and store a new value in the memory pointed to by
                              // pNumber, the integer variable called "number". Note "number" was changed, not "pNumber".




int main(int argc, char **argv)
{

}