#include<iostream>

// !! main function and command-line arguments

All C++ programs must have a main function. If you try to compile a C++ program without a main function, the compiler raises an error.
The main function is where your source code begins execution, but before a program enters the main function, all static class members 
without explicit initializers are set to zero.

The main function:
1. Can't be overloaded
2. Can't be declared as inline
3. Can't be declared as static
4. Can't have its address taken
5. Can't be called from your program

// !! The main function signature

The main function doesn't have a declaration, because it's built into the language. If it did, the declaration syntax for main would 
look like this:

int main();
int main(int argc, char *argv[]);

If no return value is specified in main, the compiler supplies a return value of zero. 


// !! Standard command-line arguments

The arguments for main allow convenient command-line parsing of arguments. The types for argc and argv are defined by the language. 
The names argc and argv are traditional, but you can name them whatever you like.

The argument definitions are as follows:

// !! argc

An integer that contains the count of arguments that follow in argv. The argc parameter is always greater than or equal to 1.


// !! argv

An array of null-terminated strings representing command-line arguments entered by the user of the program. By convention, argv[0] is 
the command with which the program is invoked. argv[1] is the first command-line argument. The last argument from the command line is 
argv[argc - 1], and argv[argc] is always NULL.


By convention, argv[0] is the filename of the program.

int main(int argc, char **argv)
{

}