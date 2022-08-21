
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1,2};
int y[2] = {3,4};
int z[2];

int main(int argc, char **argv){
    void *handle = NULL;
    void (*addvec) (int *, int *, int *, int);

    handle = dlopen("./libvector.so", RTLD_LAZY);
    
    if(!handle){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    addvec = dlsym(handle, "addvec");

    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    addvec(x, y, z, 2);

    if(dlclose(handler) < 0) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    return 0;
}