#include <atomic>
#include <thread>
#include <iostream>

class Spinlock {
    std::atomic<int64_t> locked; // 0 - unlocked, 1 - locked
public:
    void Lock() {
        while (locked.exchange(1) == 1) {}
    }

    void Unlock() {
        locked.store(0);
    }
};

int main() {
      
}
