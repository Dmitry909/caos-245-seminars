#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }
    while (true) {
    int pt = fork();
    if (pt == 0) {
        const char ** params = argv + 1;
        int tri = execvp(argv[1], &argv[2]);
        return 1; 
    }
    int ans_code;
    waitpid(pt, &ans_code, -1);
    if (ans_code == WIFEXITED) {
        
    }
        // wait process (waitpit)

        // find exit status or signal
        // use WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
    }

    return 0;
}
