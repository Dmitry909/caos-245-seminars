#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

const size_t GB20 = 20'000'000'000;

int main() {
    int fd = open("20GB_file", O_RDWR);
    void* p = mmap(NULL, GB20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    std::cout << "mmap failed?: " << (p == MAP_FAILED) << std::endl;
    
    char* s = (char*)p;
    s[GB20 - 1] = 'b';
    munmap(p, GB20);
}
