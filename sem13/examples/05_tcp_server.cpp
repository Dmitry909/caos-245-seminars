#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <arpa/inet.h>

// init_server инициализирует сервер и возвращает сокет
int init_server(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0; // 0.0.0.0
    sin.sin_port = htons(port);

    bind(socket_fd, (sockaddr*)&sin, sizeof(sin));
    listen(socket_fd, 5); // есть ли смысл ставить больше?

    return socket_fd;
}

std::tuple<int, sockaddr_storage, socklen_t> get_connection(int socket_fd) {
    sockaddr_storage peer{};
    socklen_t peer_len = sizeof(peer);
    int accepted_socket = accept(socket_fd, (sockaddr*)&peer, &peer_len);
    return {accepted_socket, peer, peer_len};
}

int main(int argc, char **argv) {
    // 1. Инициализируем сервер
    int socket_fd = init_server(3333);

    // 2. Принимаем соединение
    auto [accepted_socket, peer, peer_len] = get_connection(socket_fd);

    assert(peer.ss_family == AF_INET);
    auto peer_ipv4 = (sockaddr_in*)&peer;
    char peer_addr_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &peer_ipv4->sin_addr, peer_addr_str, sizeof(peer_addr_str));
    std::cout << "Received connection from " << peer_addr_str << ":" << ntohs(peer_ipv4->sin_port) << std::endl;
}
