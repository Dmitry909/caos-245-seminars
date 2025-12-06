#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // check args

    while (true) {
        // launch process

        // wait process (waitpit)

        // find exit status or signal
        // use WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
    }

    return 0;
}
