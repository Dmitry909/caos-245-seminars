#include <iostream>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void foo(int a, int b) {
    std::cout << a + b << std::endl;
}

void call_func(void (*ptr)(int, int)) {
    ptr(2, 3);
}

int main() {
    void (*foo_ptr)(int, int) = foo;
    foo_ptr(1, 2);
    call_func(foo_ptr);
}
