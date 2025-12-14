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
        SOCK_STREAM,                    // SOCK_STREAM = TCP
        0                           // 0 = из флагов очевидно, какой использовать
    );
    if (socket_fd == -1) {
        std::cerr << "socket failed" << std::endl;
        exit(1);
    }

    sockaddr_in target{};
    target.sin_family = AF_INET;
    inet_pton(AF_INET, ip.data(), &target.sin_addr); // перевод строки 1.2.3.4 в 4 байта
    target.sin_port = htons(port);
    int connect_result = connect(socket_fd, (sockaddr*)&target, sizeof(target));
    if (connect_result == -1) {
        std::cerr << "connect failed" << std::endl;
        exit(1);
    }

    return socket_fd;
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

std::string getResponse(int socket_fd) {
    char buf[4096];
    ssize_t bytes_got = recv(socket_fd, buf, sizeof(buf), 0);
    if (bytes_got == -1) {
        std::cerr << "recv failed: " << strerror(errno) << std::endl;
        exit(1);
    }
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
    std::cout << "response: " << response << std::endl;

    // 4. Закрываем сокет
    close(socket_fd);
}
