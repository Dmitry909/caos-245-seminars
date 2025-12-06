#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    std::cout << "hello\n";
    std::cout.flush();

    pid_t child_pid = fork();
    if (child_pid == 0) {
        std::cout << "From child" << std::endl;
        std::cout << getpid() << ' ' << getppid() << std::endl;
        std::exit(0);
    }
    std::cout << "Parent of " << child_pid << std::endl;

    waitpid(child_pid, nullptr, 0);
    std::cout << "Child returned" << std::endl;
}
