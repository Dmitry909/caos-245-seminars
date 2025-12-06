#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char c;
    while (read(fd, &c, 1) > 0) {
    }
    close(fd);
    return 0;
}
