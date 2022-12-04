#include <iostream>
#include <string>
#include <stdlib.h>

// ulimit -c unlimited    //大小不受限
// g++ -std=c++11 -g demo_abrt.cpp -o prog
// ./prog
// gdb SIGABRT/prog core.dump.filename
int main(int argc, char **argv) {

    // double free
    void *pc = malloc(1024);
    free(pc);
    free(pc);// 打开注释会导致错误
    std::cout << "free ok !" << std::endl;

    // call abort
    std::cout << "before call abort" << std::endl;
    // abort();
    std::cout << "after call abort" << std::endl;

    return 0;
}


// (gdb) bt
// #0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=140486253671360) at ./nptl/pthread_kill.c:44
// #1  __pthread_kill_internal (signo=6, threadid=140486253671360) at ./nptl/pthread_kill.c:78
// #2  __GI___pthread_kill (threadid=140486253671360, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
// #3  0x00007fc581539476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
// #4  0x00007fc58151f7f3 in __GI_abort () at ./stdlib/abort.c:79
// #5  0x00007fc5815806f6 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0x7fc5816d2b8c "%s\n") at ../sysdeps/posix/libc_fatal.c:155
// #6  0x00007fc581597d7c in malloc_printerr (str=str@entry=0x7fc5816d5710 "free(): double free detected in tcache 2") at ./malloc/malloc.c:5664
// #7  0x00007fc58159a12b in _int_free (av=0x7fc581710c80 <main_arena>, p=0x562fe1e18ea0, have_lock=0) at ./malloc/malloc.c:4473
// #8  0x00007fc58159c4d3 in __GI___libc_free (mem=<optimized out>) at ./malloc/malloc.c:3391
// #9  0x0000562fe05c4222 in main (argc=1, argv=0x7ffe318c39b8) at demo_abrt.cpp:14


// (gdb) bt
// #0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=139856134529984) at ./nptl/pthread_kill.c:44
// #1  __pthread_kill_internal (signo=6, threadid=139856134529984) at ./nptl/pthread_kill.c:78
// #2  __GI___pthread_kill (threadid=139856134529984, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
// #3  0x00007f32cb4c8476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
// #4  0x00007f32cb4ae7f3 in __GI_abort () at ./stdlib/abort.c:79
// #5  0x0000558158044291 in main (argc=1, argv=0x7ffcb6eb5848) at demo_abrt.cpp:19
