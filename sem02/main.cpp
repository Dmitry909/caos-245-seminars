#include <string>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

void foo();

int main(int argc, char** argv) {
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
}
