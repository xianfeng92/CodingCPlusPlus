
#include "stdlib.h"
#include "port.h"

void *operator new(size_t size) {
    return malloc(size);
}

void *operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void *p) {
    if (p != NULL) {
        free(p);
    }
}

void operator delete[](void *p) {
    if (p != NULL) {
        free(p);
    }
}

void operator delete(void *p, size_t UNUSED(size)) {
    if (p != NULL) {
        free(p);
    }
}

void operator delete[](void *p, size_t UNUSED(size)) {
    if (p != NULL) {
        free(p);
    }
}
