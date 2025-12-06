#include <iostream>
#include <stdlib.h>

int main() {
    const size_t new_calls_count = 4096 / 10;
    char* ptrs[new_calls_count];

    std::cout << "allocating:" << std::endl;
    for (size_t i = 0; i < new_calls_count; ++i) {
        ptrs[i] = new char[10];
    }
    std::cout << "ptrs[0]: " << (void*)ptrs[0] << std::endl;
    
    std::cout << "deleting:" << std::endl;
    for (size_t i = 0; i < new_calls_count; ++i) {
        delete[] ptrs[i];
    }

    std::cout << "deleted" << std::endl;
}
