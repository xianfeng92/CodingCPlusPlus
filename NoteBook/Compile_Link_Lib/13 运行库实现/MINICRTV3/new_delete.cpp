
extern "C" void malloc(unsigned int);
extern "C" void free(void *);

void operator new(unsigned int size) {
    return malloc(size);
}

void delete(void *ptr) {
    free(ptr);
}

void* operator new[](unsigned int size) {
    return malloc(size);
}

void delete[](void *ptr) {
    free(ptr);
}