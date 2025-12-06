#include <atomic>
#include <thread>
#include <iostream>

class Semaphore {
    int64_t max_users;
    std::atomic<int64_t> cnt_users;
public:
    Semaphore(int64_t users): max_users(users) {
        cnt_users.store(0);
    }

    void Lock() {
        int64_t current_users;
        while (true) {
            current_users = cnt_users.load();
            if (current_users == max_users) {
                continue;
            }
            if (cnt_users.compare_exchange_strong(current_users, current_users + 1)) {
                break;
            }
        }
    }

    void Unlock() {
        cnt_users.fetch_sub(1);
    }
};

Semaphore semaphore(4);

int main() {
    
}
