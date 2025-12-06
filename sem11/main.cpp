#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <mutex>
#include <unistd.h>

double l = 0;
double r = 100000;
double step = 0.0001;
std::vector<double> results;
std::mutex synchronize_push_back;

double func(double x) {
    return 2 + 3*x;
}

void calc(double l, double r, double step) {
    double result = 0;
    while (l + step < r) {
        result += func(l + step / 2) * step;
        l += step;
    }
    result += func(l + (r - l) / 2) * (r - l);
    synchronize_push_back.lock();
    results.push_back(result);
    std::cout << "result: " << result << std::endl;
    synchronize_push_back.unlock();
}

int main() {
    size_t cnt_workers = 2;
    std::vector<std::thread> workers(cnt_workers);
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i] = std::thread(
            calc,
            l + (r - l) / cnt_workers * i,
            l + (r - l) / cnt_workers * (i + 1),
            step
        );
    }
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i].join();
    }
    double result = 0;
    for (size_t i = 0; i < cnt_workers; ++i) {
        result += results[i];
    }
    std::cout << std::fixed << std::setprecision(15) << "total result: " << result << std::endl;
}
