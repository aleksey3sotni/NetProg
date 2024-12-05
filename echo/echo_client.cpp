#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

using namespace std;

int main() {
    // Адрес сервера
    const char* server_ip = "172.16.40.1";
    int server_port = 7;

    // Создание сокета
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    // Заполнение структуры адреса
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    // Подключение к серверу
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Ошибка подключения к серверу" << endl;
        close(sockfd); // Закрытие сокета в случае ошибки
        return 1;
    }

    // Ввод сообщения
    cout << "Введите сообщение: ";
    string message;
    getline(cin, message);

    // Отправка сообщения
    if (send(sockfd, message.c_str(), message.length(), 0) < 0) {
        cerr << "Ошибка отправки сообщения" << endl;
        close(sockfd); // Закрытие сокета в случае ошибки
        return 1;
    }

    // Получение ответа
    char buffer[1024] = {0}; // Инициализация буфера
    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        cerr << "Ошибка получения ответа" << endl;
        close(sockfd); // Закрытие сокета в случае ошибки
        return 1;
    }

    buffer[bytes_received] = '\0'; // Завершение строки нулевым символом

    // Вывод ответа
    cout << "Ответ сервера: " << buffer << endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}
