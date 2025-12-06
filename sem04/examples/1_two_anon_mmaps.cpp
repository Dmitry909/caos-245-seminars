#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>

const size_t mmap_size = 4000;

int main() {
    void* p1 = mmap(nullptr, mmap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    std::fill(p1, p1+mmap_size, 'a');
    void* p2 = mmap(nullptr, mmap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (p1 > p2) {
        std::swap(p1, p2);
    }
    std::cout << "p1:   " << p1 << std::endl;
    std::cout << "p2:   " << p2 << std::endl;
    std::cout << "diff: " << (char*)p2 - (char*)p1 << std::endl;
}
