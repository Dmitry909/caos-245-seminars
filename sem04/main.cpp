#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>

int main() {
    std::cout << "hello\n";
    std::cout.flush();

    pid_t child_pid = fork();
    if (child_pid == 0) {
        std::cout << "From child" << std::endl;
        sleep(10000);
        std::exit(0);
    }
    std::cout << "Parent of " << child_pid << std::endl;
    exit(0);
}
