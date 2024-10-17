#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 13
#define BUFFER_SIZE 1024

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Создание UDP сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // Инициализация адреса сервера
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Важно: проверьте корректность
    if (inet_aton("172.16.40.1", &serv_addr.sin_addr) == 0) {
        fprintf(stderr, "Неверный адрес: %s\n", "172.16.40.1");
        exit(EXIT_FAILURE);
    }

    // Отправка запроса (пустого в данном случае)
    if (sendto(sockfd, "", 0, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("Ошибка отправки");
      exit(EXIT_FAILURE);
    }

    // Получение ответа
    socklen_t addrlen = sizeof(serv_addr);
    n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &addrlen);
    if (n < 0) {
        perror("Ошибка получения данных");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0'; // КРИТИЧНО: добавляем нуль-терминатор

    // Вывод ответа
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}
