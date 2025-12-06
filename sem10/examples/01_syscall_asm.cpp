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

    // Args: rdi, rsi, rdx, r10, r8, r9
    // Clobbers: rcx, r11
    asm(R"(
        syscall
    )"
        : "=a"(res)
        : "a"(SYS_write), "D"(1), "S"(message), "d"(strlen(message))
        : "rcx", "r11");
}
