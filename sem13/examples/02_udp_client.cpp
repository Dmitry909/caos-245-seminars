#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <arpa/inet.h>

// initUDPForSending Создаёт сокет и sockaddr_in для дальнейшей передачи их в send_to
std::pair<int, sockaddr_in> initUDPForSending(std::string ip, int port) {
    int socket_fd = socket( // создание сокета
        AF_INET,                      // IPv4
        SOCK_DGRAM,                    // SOCK_DGRAM = UDP
        0                           // 0 = из флагов очевидно, какой использовать
    );

    sockaddr_in target{};
    target.sin_family = AF_INET;
    inet_pton(AF_INET, ip.data(), &target.sin_addr); // перевод строки 1.2.3.4 в 4 байта
    target.sin_port = htons(port);

    return {socket_fd, target};
}

// sendToSocket Отправляет в UDP-сокет сообщение
void sendToSocket(int socket_fd, std::string message, const sockaddr_in& target) {
    // TODO дописывать, если записалось не полностью.
    sendto(socket_fd, message.data(), message.size(), MSG_NOSIGNAL, (sockaddr*)&target, sizeof(target));
}

// getResponseFromUDP Читает из UDP-сокета
std::string getResponseFromUDP(int socket_fd) {
    char buf[4096];
    sockaddr_in from_addr;
    socklen_t addr_len;
    size_t bytes_got = recvfrom(socket_fd, buf, sizeof(buf), 0, (sockaddr*)&from_addr, &addr_len);
    return std::string(buf, bytes_got);
}

std::string getResponse(int socket_fd) {
    char buf[4096];
    size_t bytes_got = recv(socket_fd, buf, sizeof(buf), 0);
    return std::string(buf, bytes_got);
}

int main(int argc, char **argv) {
    assert(argc == 4);

    std::string ip_str(argv[1]);
    int port = atoi(argv[2]);
    std::string message(argv[3]);

    // 1. Создаём нужные данные в ядре ОС и у себя для дальнейших отправок.
    auto [socket_fd, target] = initUDPForSending(ip_str, port);

    // 2. Отправляем сообщение серверу.
    sendToSocket(socket_fd, message, target);

    // 3. Читает из сокета
    getResponseFromUDP(socket_fd);

    // 4. Закрываем сокет
    close(socket_fd);
}
