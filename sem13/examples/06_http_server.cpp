#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <arpa/inet.h>
#include <string>

// init_server инициализирует сервер и возвращает сокет
int init_server(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Установка опции для повторного использования адреса
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    addr.sin_port = htons(port);

    if (bind(socket_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(socket_fd, 5) < 0) {
        perror("listen failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    return socket_fd;
}

std::tuple<int, sockaddr_storage, socklen_t> get_connection(int socket_fd) {
    sockaddr_storage peer{};
    socklen_t peer_len = sizeof(peer);
    int accepted_socket = accept(socket_fd, (sockaddr*)&peer, &peer_len);
    if (accepted_socket < 0) {
        perror("accept failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    return {accepted_socket, peer, peer_len};
}

// Функция для отправки данных клиенту
bool send_all(int socket, const char* data, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        ssize_t sent = send(socket, data + total_sent, length - total_sent, 0);
        if (sent <= 0) {
            return false; // Ошибка отправки
        }
        total_sent += sent;
    }
    return true;
}

int main(int argc, char **argv) {
    // 1. Инициализируем сервер
    int socket_fd = init_server(80);
    std::cout << "Server started on port 80\n";

    while (true) {
        // 2. Принимаем соединение
        auto [accepted_socket, peer, peer_len] = get_connection(socket_fd);

        assert(peer.ss_family == AF_INET);
        auto peer_ipv4 = (sockaddr_in*)&peer;
        char peer_addr_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peer_ipv4->sin_addr, peer_addr_str, sizeof(peer_addr_str));
        std::cout << "Received connection from " << peer_addr_str << ":" << ntohs(peer_ipv4->sin_port) << std::endl;

        // 3. Формируем HTTP-ответ с HTML-страницей
        std::string http_response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Connection: keep-alive\r\n"
            "\r\n"
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <title>Simple HTTP Server</title>\n"
            "    <style>\n"
            "        body {\n"
            "            font-family: Arial, sans-serif;\n"
            "            margin: 40px;\n"
            "            background-color: #f0f0f0;\n"
            "        }\n"
            "        .container {\n"
            "            max-width: 800px;\n"
            "            margin: 0 auto;\n"
            "            background-color: white;\n"
            "            padding: 30px;\n"
            "            border-radius: 10px;\n"
            "            box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n"
            "        }\n"
            "        h1 {\n"
            "            color: #333;\n"
            "            border-bottom: 2px solid #4CAF50;\n"
            "            padding-bottom: 10px;\n"
            "        }\n"
            "        .info {\n"
            "            background-color: #e8f5e9;\n"
            "            padding: 15px;\n"
            "            border-radius: 5px;\n"
            "            margin: 20px 0;\n"
            "        }\n"
            "        .client-ip {\n"
            "            font-weight: bold;\n"
            "            color: #4CAF50;\n"
            "        }\n"
            "        .timestamp {\n"
            "            color: #666;\n"
            "            font-size: 0.9em;\n"
            "        }\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "    <div class=\"container\">\n"
            "        <h1>Welcome to Simple HTTP Server</h1>\n"
            "        <div class=\"info\">\n"
            "            <p>This is a simple HTTP server written in C++</p>\n"
            "            <p>Your IP address: <span class=\"client-ip\">" + 
            std::string(peer_addr_str) + "</span></p>\n"
            "            <p>Port: <span class=\"client-ip\">" + 
            std::to_string(ntohs(peer_ipv4->sin_port)) + "</span></p>\n"
            "        </div>\n"
            "        <h2>Server Information</h2>\n"
            "        <ul>\n"
            "            <li>Protocol: HTTP/1.1</li>\n"
            "            <li>Server port: 3333</li>\n"
            "            <li>Connection: Closed after response</li>\n"
            "        </ul>\n"
            "        <h2>Example Features</h2>\n"
            "        <p>This server demonstrates:</p>\n"
            "        <ol>\n"
            "            <li>Raw socket programming in C++</li>\n"
            "            <li>HTTP protocol implementation</li>\n"
            "            <li>HTML content generation</li>\n"
            "            <li>Client information display</li>\n"
            "        </ol>\n"
            "        <div class=\"timestamp\">\n"
            "            Page generated by Simple HTTP Server\n"
            "        </div>\n"
            "    </div>\n"
            "</body>\n"
            "</html>";

        // 4. Отправляем ответ клиенту
        if (!send_all(accepted_socket, http_response.c_str(), http_response.length())) {
            std::cerr << "Failed to send response to client\n";
        }

        // 5. Закрываем соединение с клиентом
        close(accepted_socket);
        std::cout << "Connection closed with " << peer_addr_str << std::endl;
    }

    // 6. Закрываем серверный сокет (эта строка никогда не выполнится в бесконечном цикле)
    close(socket_fd);
    return 0;
}
