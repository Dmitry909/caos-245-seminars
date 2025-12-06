#include <atomic>
#include <thread>
#include <iostream>

int64_t counter;
std::atomic<int64_t> atomic_counter;

void func() {
    for (size_t i = 0; i < 1'000'000; ++i) {
        counter += 1;
    }
}

void func_atomic() {
    for (size_t i = 0; i < 1'000'000; ++i) {
        atomic_counter.fetch_add(1);
    }
}

int main() {
    std::thread t1(func_atomic);
    std::thread t2(func_atomic);
    t1.join();
    t2.join();
    // std::cout << counter << std::endl;
    std::cout << atomic_counter.load() << std::endl;
}
