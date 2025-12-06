#include <unistd.h>
#include <errno.h>
#include <iostream>

int main() {
    char buf[1000];
    ssize_t cnt_read = read(3, buf, 10);
    std::cout << "cnt_read: " << cnt_read << std::endl;
    buf[cnt_read] = 0;
    std::cout << "errno after read: " << errno << std::endl;
    if (errno == EBADF) {
        printf("wrong file descriptor\n");
    }
    
    write(2, buf, 10);
    std::cout << "\nerrno after write: " << errno << std::endl;
}
