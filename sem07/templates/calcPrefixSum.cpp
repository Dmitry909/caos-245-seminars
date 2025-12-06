#include <cstddef>
#include <cstdint>

void calcPrefixSumCpp(const uint64_t* arr, size_t n, uint64_t* prefix_sum) {
    if (n == 0) {
        return;
    }
    prefix_sum[0] = arr[0];
    for (size_t i = 1; i < n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }
}
