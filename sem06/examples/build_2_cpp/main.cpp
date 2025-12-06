#include <iostream>
#include "headers.h"

const char* hello = "hELLO, ";
const char* caos = "caos";

char* change_case(char* s) {
    char* result = s;
    while (*s) {
        if (*s >= 'a' && *s <= 'z') {
            *s += 'A' - 'a';
        } else if (*s >= 'A' && *s <= 'Z') {
            *s += 'a' - 'A';       
        }
        ++s;
    }
    return result;
}

int main() {
    char buf[7+4+1];
    std::cout << change_case(concat(hello, caos, buf)) << std::endl;
}
