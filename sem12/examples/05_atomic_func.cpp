#include <atomic>
#include <thread>
#include <iostream>

int64_t func(int64_t x) {
    return x*x - 10;
}

void apply_func(std::atomic<int64_t>& a) {
    int64_t expected = a.load();
    while (!a.compare_exchange_strong(expected, func(expected))) {}
}

int main() {
    std::atomic<int64_t> a(5);
    apply_func(a);
    std::cout << a.load() << std::endl;
}
