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

std::vector<std::vector<int64_t>> multiply(
    size_t n,
    size_t m,
    size_t k,
    const std::vector<std::vector<int64_t>>& a, // n x m
    const std::vector<std::vector<int64_t>>& b  // m x k
) {
    std::vector<std::vector<int64_t>> res(n, std::vector<int64_t>(k, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            for (size_t w = 0; w < m; ++w) {
                res[i][j] += a[i][w] * b[w][j];
            }
        }
    }
    return res;
}

int main() {
    size_t n = 500, m = 1000, k = 200;
}
