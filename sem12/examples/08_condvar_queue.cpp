#include <atomic>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>

std::mutex m;
std::condition_variable cv;
std::queue<int64_t> q;
bool closed = false;
const int MAX_SIZE = 100;

void worker() {
    for (size_t i = 0; i < 1'000'000; ++i) {
        m.lock();
        q.push(i);
        m.unlock();
        cv.notify_one();
    }
    m.lock();
    closed = true;
    m.unlock();
}

int main() {
    std::thread t(worker);
    int64_t sum = 0;
    while (true) {
        std::unique_lock<std::mutex> lk(m);
        if (closed) {
            break;
        }
        cv.wait(lk, []() { return !q.empty(); });
        sum += q.front();
        q.pop();
    }

    while (!q.empty()) {
        sum += q.front();
        q.pop();
    }
    std::cout << "result: " << sum << std::endl;

    t.join();
}
