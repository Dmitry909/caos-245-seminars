#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

const size_t GB100 = 100'000'000'000;

int main() {
    char* s = (char*)mmap(nullptr, GB100, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    int e = errno;
    if (s == MAP_FAILED) {
        perror("MAP_FAILED");
        std::cout << "errno: " << errno << std::endl; 
        return 0;
    }

    std::cout << "sleeping..." << std::endl;
    sleep(1000);
    munmap(s, GB100);
}
