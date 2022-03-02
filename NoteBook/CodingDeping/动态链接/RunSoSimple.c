#include<stdio.h>
#include<dlfcn.h>

int main(int argc, char **argv)
{
    void *handle;
    double (*func)(double);
    char *error;

    handle = dlopen(argv[1], RTLD_NOW);
    if (handle == NULL)
    {
        printf("Open Library %s error: %s\n", argv[1], dlerror());
        return -1;
    }
    func = dlsym(handle, "sin");
    if ((error = dlerror()) != NULL)
    {
        printf("Symbol is not found: %s\n", error);
    }
    else
    {
        printf("%f \n", func(3.1415926 / 2));
    }
    dlclose(handle);
}