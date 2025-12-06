#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int64_t> a;

int main() {
    std::cout << std::boolalpha;

    a.store(10);
    int64_t expected = 10;
    std::cout << "CAS result:   " << a.compare_exchange_strong(expected, 20) << std::endl;
    std::cout << "old value:    " << expected << std::endl;
    std::cout << "atomic value: " << a.load() << std::endl;
}
