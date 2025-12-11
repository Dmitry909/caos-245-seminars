#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    assert(argc == 4);

    const char* ip_str = argv[1];
    int port = atoi(argv[2]);
    const char* message = argv[3];

    int socket_fd = socket(
        AF_INET,                      // IPv4
        SOCK_STREAM | SOCK_CLOEXEC,     // SOCK_STREAM = TCP
        0                           // 0 = из флагов очевидно, какой использовать
    );
}
