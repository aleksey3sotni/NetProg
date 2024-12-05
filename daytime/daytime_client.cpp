#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

using namespace std;

int main() {

    const char* server_ip = "172.16.40.1";
    int server_port = 13;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    char request[1024] = "";
    if (sendto(sockfd, request, sizeof(request), 0, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Ошибка отправки запроса" << endl;
        close(sockfd);
        return 1;
    }

    char buffer[1024] = {0}; // Инициализация буфера нулями
    socklen_t addr_len = sizeof(server_addr);
    int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&server_addr, &addr_len);
    if (bytes_received < 0) {
        cerr << "Ошибка получения ответа" << endl;
        close(sockfd);
        return 1;
    }

    buffer[bytes_received] = '\0'; // Завершение строки нулевым символом

    cout << "Текущее время: " << buffer << endl;

    close(sockfd);

    return 0;
}
