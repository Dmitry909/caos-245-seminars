#include <iostream>
#include <thread>

double func(double x) {
    return 2 - 3*x + x*x;
}

void calc_integral(double l, double r, double step) {
    while (true) {
        l += 0.01;
    }
    // double result = 0;
    // while (l + step < r) {
    //     result += func(l + step / 2) * step;
    //     l += step;
    // }
    // result += func(l + (r - l) / 2) * (r - l);
    // std::cout << result << std::endl;
}

int main() {
    double l = 0;
    double r = 10;
    double step = 0.00001;
    std::thread t1(calc_integral, l, r, step);
    std::thread t2(calc_integral, l, r, step);
    std::thread t3(calc_integral, l, r, step);
    std::thread t4(calc_integral, l, r, step);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
