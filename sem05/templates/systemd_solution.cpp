#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return 1;
    }

    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            execvp(argv[1], &argv[1]);
            perror("execvp");
            exit(1);
        } else {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
                return 1;
            }

            if (WIFEXITED(status)) {
                int code = WEXITSTATUS(status);
                printf("Process exited with code %d\n", code);
                printf("Restarting process...\n");
            } else if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                printf("Process killed by signal %d\n", sig);
                printf("Restarting process...\n");
            } else {
                printf("Process ended unexpectedly\n");
                printf("Restarting process...\n");
            }
        }
    }

    return 0;
}
