#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <chrono>

extern "C" void pref(const uint64_t* from, size_t n, uint64_t* to);

// void pref(const uint64_t* from, size_t n, uint64_t* to) {
//     if (n == 0) {
//         return;
//     }
//     to[0] = from[0];
//     for (size_t i = 1; i < n; ++i) {
//         to[i] = to[i - 1] + from[i];
//     }
// }

int main() {
    uint64_t from[6] = {1, 2, 3, 4, 5, 6};
    uint64_t to[6];
    pref(from, 6, to);
    for (size_t i = 0; i < 6; ++i) {
        std::cout << to[i] << ' ';
    }
    std::cout << std::endl;
}
