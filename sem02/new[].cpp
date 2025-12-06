#include <string>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char** argv) {
    const size_t len = 5 * 1024 * 1024 * 1024ll;
    char* p = new char[len];

    std::cout << "start sleeping" << std::endl;
    sleep(1000);
}
