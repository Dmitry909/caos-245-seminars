#include <iostream>
#include <cstdint>

uint64_t AddAsmInline(uint64_t a, uint64_t b) {
    uint64_t res;
    asm(R"(
        mov %1, %0
        add %2, %0
    )"
        : "=&r"(res)
        : "r"(a), "r"(b)
        : "cc");
    return res;
}

int main() {
    uint64_t a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
}
