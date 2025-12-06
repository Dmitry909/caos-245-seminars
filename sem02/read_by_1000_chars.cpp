#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char c[1000];
    std::cout << fd << std::endl;
    while (read(fd, c, 1000) > 0) {
    }
    close(fd);
    return 0;
}
