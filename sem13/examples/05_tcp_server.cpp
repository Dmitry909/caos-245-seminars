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

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0; // 0.0.0.0
    addr.sin_port = htons(port);

    bind(socket_fd, (sockaddr*)&addr, sizeof(addr));
    listen(socket_fd, 5); // есть ли смысл ставить больше?

    return socket_fd;
}

std::tuple<int, sockaddr_storage, socklen_t> get_connection(int socket_fd) {
    sockaddr_storage peer{};
    socklen_t peer_len = sizeof(peer);
    int accepted_socket = accept(socket_fd, (sockaddr*)&peer, &peer_len);
    return {accepted_socket, peer, peer_len};
}

// sendToSocket Отправляет в TCP-сокет сообщение
ssize_t sendToSocket(int socket_fd, std::string message) {
    // TODO дописывать, если записалось не полностью.
    ssize_t sent = send(socket_fd, message.data(), message.size(), MSG_NOSIGNAL);
    if (sent == -1) {
        std::cerr << "send failed" << std::endl;
        exit(1);
    }
    return sent;
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

    // 3. Отправляем сообщение клиенту.
    std::string response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Connection: keep-alive\r\n"
            "\r\n"
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <title>Simple HTTP Server</title>\n"
            "</head>\n"
            "<body>\n"
            "    <div class=\"container\">\n"
            "        <h1>Welcome to Simple HTTP Server</h1>\n"
            "    </div>\n"
            "</body>\n";

    sendToSocket(accepted_socket, response);
    close(accepted_socket);

    sleep(1000);

    // 4. Закрываем сокеты
    close(socket_fd);
}
