#include <iostream>
#include <thread>
#include <vector>

std::vector<int> v;

void pb() {
    for (size_t i = 0; i < 100000000; ++i) {
        v.push_back(i);
    }
}

int main() {
    std::thread t(pb);
    pb();
    t.join();
}
