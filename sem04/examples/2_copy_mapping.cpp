#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>

const size_t MB1 = 1024 * 1024 * 1024;

void check_for_mmap_failed(void* p, const char* variable_name) {
    if (p == MAP_FAILED) {
        std::cerr << variable_name << " == MAP_FAILED" << std::endl;
        exit(1);
    }
    std::cout << variable_name << " != MAP_FAILED" << std::endl;
}

int main() {
    void* p =     mmap(nullptr, MB1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    check_for_mmap_failed(p, "p");

    void* p_new = mmap(nullptr, MB1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    check_for_mmap_failed(p_new, "p_new");

    void* p_remap = mremap(p, 0, MB1, MREMAP_FIXED | MREMAP_MAYMOVE, p_new);
    check_for_mmap_failed(p_remap, "p_remap");

    std::cout << "p      : " << p << std::endl;
    std::cout << "p_new  : " << p_new << std::endl;
    std::cout << "p_remap: " << p_remap << std::endl;

    auto from = (volatile int*)(p);
    auto to   = (volatile int*)(p_new);

    *from = 123;
    std::cout << "to:   " << *to << std::endl;
    *to = 456;
    std::cout << "from: " << *to << std::endl;
}
