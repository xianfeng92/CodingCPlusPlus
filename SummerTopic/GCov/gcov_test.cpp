#include <stdio.h>

// gcc -fprofile-arcs -ftest-coverage -o gcov_test gcov_test.cpp 
// ./gcov_test
// gcov gcov_test.cpp 
int main(int argc, char **argv) {
    int i, total;
    total = 0;
    for(i = 0; i < 10; i++) {
        total += i;
    }
    if(total != 45) {
        printf("fail!\n");
    } else {
        printf("success!\n");
    }
    return 0;
}