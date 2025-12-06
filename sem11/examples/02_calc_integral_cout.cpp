#include <iostream>
#include <thread>
#include <vector>

const double l = 0;
const double r = 1000;
const double step = 0.00001;

double func(double x) {
    return 2 - 3*x + x*x;
}

void calc_integral(double l, double r, double step) {
    double result = 0;
    while (l + step < r) {
        result += func(l + step / 2) * step;
        l += step;
    }
    result += func(l + (r - l) / 2) * (r - l);
    std::cout << result << std::endl;
}

int main() {
    size_t cnt_workers = std::thread::hardware_concurrency() - 1;
    std::cout << "cnt_workers: " << cnt_workers << std::endl;

    std::vector<std::thread> workers(cnt_workers);
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i] = std::thread(
            calc_integral,
            l + (r - l) / cnt_workers * i,
            l + (r - l) / cnt_workers * (i + 1),
            step
        );
    }
    for (size_t i = 0; i < cnt_workers; ++i) {
        workers[i].join();
    }
}
