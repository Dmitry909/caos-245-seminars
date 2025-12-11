#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <arpa/inet.h>

// connectByTCP Подключается к адресу ip:port по TCP и возвращает файловый дескриптор сокета.
int connectByTCP(std::string ip, int port) {
    int socket_fd = socket( // создание сокета
        AF_INET,                      // IPv4
        SOCK_STREAM | SOCK_CLOEXEC,     // SOCK_STREAM = TCP
        0                           // 0 = из флагов очевидно, какой использовать
    );

    sockaddr_in target{};
    target.sin_family = AF_INET;
    inet_pton(AF_INET, ip.data(), &target.sin_addr); // перевод строки 1.2.3.4 в 4 байта
    target.sin_port = htons(port);
    connect(socket_fd, (sockaddr*)&target, sizeof(target));

    return socket_fd;
}

// sendToSocket Отправляет в TCP-сокет сообщение
int sendToSocket(int socket_fd, std::string message) {
    // TODO дописывать, если записалось не полностью.
    send(socket_fd, message, message.size(), MSG_NOSIGNAL);
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

    // 1. Подкючаемся к серверу.
    int socket_fd = connectByTCP(ip_str, port);

    // 2. Отправляем сообщение серверу.
    sendToSocket(socket_fd, message);

    // 3. Читаем ответ сервера.
    std::string response = getResponse(socket_fd);

    // 4. Закрываем сокет
    close(socket_fd);
}
