#include <iostream>
#include <cstdint>

uint64_t SumAsm(uint64_t* p, size_t n) {
    // a - rax
    // b - rbx
    // c - rcx
    // d - rdx
    // D - rdi
    // S - rsi
    uint64_t res = 0;
    asm volatile(R"(
        # TODO
        )"
        :
        :
        :);
    return res;
}

int main() {
    uint64_t a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << SumAsm(a, 10) << std::endl;
}
