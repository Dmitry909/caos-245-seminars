#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>

const size_t MB1 = 1024 * 1024;

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
    for (size_t i = 0; i < MB1; ++i) {
        char* s = (char*)p;
        s[i] = i % 128;
    }

    void* p_new = mmap(nullptr, MB1 * 2, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    check_for_mmap_failed(p_new, "p_new");

    void* p_remap = mremap(p, 0, MB1, MREMAP_FIXED | MREMAP_MAYMOVE, p_new);
    check_for_mmap_failed(p_remap, "p_remap");

    std::cout << "p      : " << p << std::endl;
    std::cout << "p_new  : " << p_new << std::endl;
    std::cout << "p_remap: " << p_remap << std::endl;

    int munmap_res = munmap(p, MB1);
    if (munmap_res != 0) {
        std::cerr << "munmap failed" << std::endl;
        exit(1);
    } else {
        std::cout << "munmap succeed" << std::endl;
    }

    char* s = (char*)p_remap;

    size_t old_sum = 0;
    size_t total_sum = 0;
    for (size_t i = 0; i < MB1 * 2; ++i) {
        if (i >= MB1) {
            s[i] = i % 128;
        } else {
            old_sum += s[i];
        }
        total_sum += s[i];
    }
    std::cout << "old_sum:   " << old_sum << std::endl;
    std::cout << "total_sum: " << total_sum << std::endl;
}
