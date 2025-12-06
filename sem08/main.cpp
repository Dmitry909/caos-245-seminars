#include <iostream>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Задача:
// Прочитать из файла структуры с помощью read
// Сформировать из них строку для питона
// Вычислить ее питоном (форкнувшись и дождавшись)
// Результат получить через pipe
// Вывести его

struct A {
    int64_t sign; // -1 1 -- знак
    int64_t value; // само число
};

int main() {
    // A a[3] = {{1, 10}, {-1, 20}, {-1, 55}};
    // std::cout << (void*)(&a[0]) << std::endl;
    // std::cout << (void*)(&a[1]) << std::endl;
    // std::cout << (void*)(&a[2]) << std::endl;
    // size_t fd = open("file", O_CREAT | O_WRONLY);
    // write(fd, a, sizeof(A) * 3);

    size_t fd = open("file", O_RDONLY);
    A operands[3];
    read(fd, operands, sizeof(operands));
    for (size_t i = 0; i < 3; ++i) {
        std::cout << operands[i].sign << ' ' << operands[i].value << std::endl;
    }

    std::string s;
    for (size_t i = 0; i < 3; ++i) {
        if (operands[i].sign == -1) {
            char buf[25];
            sprintf(buf, "-%ld", operands[i].value);
            s += buf;
        } else if (operands[i].sign == 1) {
            char buf[25];
            sprintf(buf, "+%ld", operands[i].value);
            s += buf;
        }
    }
    s = "print(" + s + ")";

    int pipe_fd[2];
    pipe2(pipe_fd, O_CLOEXEC);
    
    size_t child_pid = fork();
    if (child_pid == 0) {
        // child
        size_t result;
        dup2(pipe_fd[1], 1);
        const char* const args[2] = {"-c", s.data()};
        // const char ** args2 = args;
        execvp("python3", args);
        // write(pipe_fd[1], &result, sizeof(result));
        return 0;
    }
    waitpid(child_pid, nullptr, 0);
    int64_t result;
    read(pipe_fd[0], &result, sizeof(result));
    std::cout << result << std::endl;
}
