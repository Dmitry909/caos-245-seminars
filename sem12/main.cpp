#include <atomic>
#include <thread>
#include <condition_variable>
#include <iostream>

std::mutex m;
std::condition_variable cv;
std::atomic<int64_t> finished(0);

void worker() {
    // work...
    finished.store(1);
    cv.notify_one();
    std::cout << "worker notified" << std::endl;
}

int main() {
    std::thread t(worker);
    std::unique_lock<std::mutex> lk(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (!finished.load()) {
        std::cout << "main waiting..." << std::endl;
        cv.wait(lk);
    }

    t.join();
}
