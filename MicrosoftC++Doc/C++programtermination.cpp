#include<iostream>



// !! C++ program termination

In C++, you can exit a program in these ways:

1. Call the exit function.
2. Call the abort function.
3. Execute a return statement from main.


// !! exit function

The exit function, declared in <stdlib.h>, terminates a C++ program. The value supplied as an argument to exit is returned to the 
operating system as the program's return code or exit code. By convention, a return code of zero means that the program completed 
successfully. You can use the constants EXIT_FAILURE and EXIT_SUCCESS, also defined in <stdlib.h>, to indicate success or failure 
of your program.


// !! abort function



// !! atexit function


int main(int argc, char **argv)
{

}