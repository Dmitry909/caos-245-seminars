#include <atomic>
#include <thread>

std::atomic<uint64_t> counter(0);

void fetch() {
    counter.fetch_add(123);
    counter.fetch_sub(123);
    counter.fetch_or(123);
    counter.fetch_and(123);
    counter.fetch_xor(123);
}

void load() {
    counter.load();
}

void store() {
    counter.store(123);
}

void exchange() {
    counter.exchange(123);
}

void cas() {
    uint64_t expected = 100;
    counter.compare_exchange_weak(expected, 123);
    counter.compare_exchange_strong(expected, 123);
}
