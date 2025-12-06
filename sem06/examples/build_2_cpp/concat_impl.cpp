#include "headers.h"

char* concat(const char* a, const char* b, char* buf) {
    char* result = buf;

    while (*a) {
        *buf = *a;
        ++a;
        ++buf;
    }
    while (*b) {
        *buf = *b;
        ++b;
        ++buf;
    }
    *buf = 0;

    return result;
}
