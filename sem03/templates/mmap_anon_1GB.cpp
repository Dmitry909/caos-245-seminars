#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

const size_t GB1 = 1'000'000'000;

int main() {
    char* s = (char*)mmap(nullptr, GB1, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (s == MAP_FAILED) {
        std::cout << "MAP_FAILED" << std::endl;
        return 0;
    }
    for (size_t i = 0; i < GB1; ++i) {
        s[i] = i % 100;
    }

    std::cout << "sleeping..." << std::endl;
    sleep(1000);
    munmap(s, GB1);
}
