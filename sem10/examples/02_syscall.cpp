#include <iostream>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    const char* message = "Hello\n";
    uint64_t res;

    syscall(SYS_write, 1, message, strlen(message));
}
