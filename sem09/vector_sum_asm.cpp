#include <iostream>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// sum_slow вычисляет сумму в массиве по индексам с l по r включительно
// без векторных инструкций
uint32_t sum_slow(uint32_t* p, size_t l, size_t r) {
    uint32_t result = 0;
    for (size_t i = l; i <= r; ++i) {
        result += p[i];
    }
    return result;
}

// sum_slow вычисляет сумму в массиве по индексам с l по r включительно
// с векторными инструкциями
uint32_t sum_fast(uint32_t* p, size_t l, size_t r) {
    uint32_t result = 0;
    size_t i = l;

    uint32_t temp[8] = {0};
    asm(R"(
        # ymm0 = 0
    )"
    :
    :
    : "ymm0");
    for (; i + 8 <= r; i += 8) {
        asm volatile(R"(
            # ymm1 = p[i]
            # ymm0 += ymm0
        )"
            : 
            : "r"(p + i)
            : "ymm0", "ymm1"
        );   
    }
    for (size_t i = 0; i < 8; ++i) {
        result += temp[i];
    }


    for (; i <= r; ++i) {
        result += p[i];
    }
    return result;
}

int main() {
    uint32_t a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << sum_slow(a, 0, 9) << std::endl;
    std::cout << sum_fast(a, 0, 9) << std::endl;
}
