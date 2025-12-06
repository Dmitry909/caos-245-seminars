#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() {
    int fd = open("/home/dmitry/CAOS/lec2.mp4", O_RDWR);
    void* p = mmap(NULL, 440047930, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    std::cout << "mmap failed?: " << (p == MAP_FAILED) << std::endl;
    sleep(1000);
}
