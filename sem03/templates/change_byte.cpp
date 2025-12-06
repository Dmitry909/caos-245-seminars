#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

const size_t GB20 = 20'000'000'000;

void set_byte_via_mmap(char* s, size_t pos, char byte) {
    s[pos] = byte;
}

void change_via_mmap(int fd) {
    void* p = mmap(NULL, GB20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    std::cout << "mmap failed?: " << (p == MAP_FAILED) << std::endl;
    
    char* s = (char*)p;
    set_byte_via_mmap(s, GB20 - 1, 'b');
    munmap(p, GB20);
}

void set_byte_via_write(int fd, size_t pos, char byte) {
    lseek(fd, pos, SEEK_SET);
    size_t write_res = write(fd, &byte, 1);
    std::cout << "write result: " << write_res << std::endl;
}

void change_via_write(int fd) {
    set_byte_via_write(fd, GB20 - 1, 'c');
    close(fd);
}

int main() {
    int fd = open("20GB_file", O_RDWR);
    // change_via_mmap(fd);
    change_via_write(fd);
}
