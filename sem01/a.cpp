#include <cstdint>
#include <stdio.h>
#include <iostream>

int main() {
    uint32_t a = 1;
    uint32_t b = 10;
    uint32_t c = 100;
    printf("%p %lu :&a\n", &a, (uint64_t)&a);
    printf("%p %lu :&b\n", &b, (uint64_t)&b);
    printf("%p %lu :&c\n", &c, (uint64_t)&c);

    uint32_t* pa = &a;

    // uint64_t* p = (uint64_t*)&a;
    // std::cout << *p << std::endl;
    // std::cout << 4294967296ul * b + a << std::endl;

    std::cout << *(pa-1) << std::endl;
    std::cout << *(pa-2) << std::endl;
    std::cout << *(pa-3) << std::endl;
    std::cout << *(pa-4) << std::endl;
    std::cout << *(pa-5) << std::endl;
    std::cout << *(pa-6) << std::endl;
    std::cout << *(pa-7) << std::endl;
    std::cout << *(pa-8) << std::endl;

    uint32_t* pp = (uint32_t*)563346365;
    std::cout << *(pp) << std::endl;
}
