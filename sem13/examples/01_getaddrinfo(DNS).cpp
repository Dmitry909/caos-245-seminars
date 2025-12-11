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
    assert(argc == 3);
    const char *host = argv[1];
    const char *port = argv[2];

    // 1. getaddrinfo
    struct addrinfo hints{};
    struct addrinfo* res = nullptr;

    hints.ai_family = AF_UNSPEC;        // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP socket
    hints.ai_flags = 0;
    hints.ai_protocol = 0;              // Any protocol

    int err = getaddrinfo(host, port, &hints, &res);
    if (err != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(err) << "\n ";
        return 1;
    }

    int sockfd = -1;
    struct addrinfo* rp;
    for (rp = res; rp != nullptr; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1) {
            continue;
        }
        bool success = connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1;
        if (rp->ai_family == AF_INET) {
            char buf[INET_ADDRSTRLEN]{};
            inet_ntop(rp->ai_family, &((sockaddr_in*)rp->ai_addr)->sin_addr, buf, sizeof(buf));
            std::cout << buf;
        } // TODO else with AF_INET6
        std::cout << " " << (success ? "Success" : "Failure") << std::endl;

        close(sockfd);
        sockfd = -1;
    }

    freeaddrinfo(res);
}
