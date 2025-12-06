#include <iostream>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <chrono>

std::random_device rd;
std::mt19937 g(rd());

int64_t sum(
    const std::vector<int32_t>& data,
    const std::vector<size_t>& positions
) {
    int64_t result = 0;
    for (auto i : positions) {
        result += data[i];
    }
    return result;
}

int main() {
    size_t n = 50'000'000;
    std::vector<int32_t> data(n);
    std::vector<size_t> positions(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = g() % std::numeric_limits<int32_t>::max();
        positions[i] = i; // 0, 1, 2, 3, ...
    }

    std::shuffle(positions.begin(), positions.end(), g); // 2, 0, 3, 1, ...

    auto start = std::chrono::high_resolution_clock::now();
    auto res = sum(data, positions);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "duration: " << duration.count() << std::endl;
    std::cout << "res: " << res << std::endl;
}
