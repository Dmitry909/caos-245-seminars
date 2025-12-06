#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <mutex>

const double l = 0;
const double r = 100000;
const double step = 0.00001;
std::vector<double> results;
std::mutex mt; // иначе не назвать :)

double func(double x) {
    return 2 + 3*x;
}

void calc_integral(size_t worker_id, double l, double r, double step) {
    double result = 0;
    while (l + step < r) {
        result += func(l + step / 2) * step;
        l += step;
    }
    result += func(l + (r - l) / 2) * (r - l);
    mt.lock();
    results.push_back(result);
    mt.unlock();
}

int main() {
    size_t cnt_workers = std::thread::hardware_concurrency() - 1;
    std::cout << "cnt_workers: " << cnt_workers << std::endl;

    std::vector<std::thread> workers(cnt_workers);
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i] = std::thread(
            calc_integral,
            i,
            l + (r - l) / cnt_workers * i,
            l + (r - l) / cnt_workers * (i + 1),
            step
        );
    }
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i].join();
    }

    double result = 0;
    for (auto r : results) {
        result += r;
    }
    std::cout << std::fixed << std::setprecision(5) << "result: " << result << std::endl;
}
