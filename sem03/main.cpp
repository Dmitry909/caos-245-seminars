#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "exactly 2 args required" << std::endl;
        return 1;
    }

    int fd = open("binary/common_output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    for (long i = 0; i < 1024 * 1024; i++) {
        lseek(fd, 0, SEEK_END);
        // тут может вклиниться другой процесс
        size_t written = write(fd, argv[1], 1);
        if (written != 1) {
            perror("Write error");
            std::cerr << "write result: " << written << std::endl;
            close(fd);
            return 1;
        }
    }

    close(fd);
}
