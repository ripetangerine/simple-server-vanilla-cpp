#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("1 - 소켓 생성됌 : fd = %d\n\n", server_fd);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY
    };
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    printf("2 - 포트바인딩\n");

    listen(server_fd, 5);
    printf("3 - 연결 대기\n");

    int client_fd = accept(server_fd, NULL, NULL);
    printf("4 - 클라이언트 연결 fd=%d\n", client_fd);

    char* res = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "Hello world";
    send(client_fd, res, 13, 0);

    closesocket(client_fd);
    closesocket(server_fd);

    return 0;
}