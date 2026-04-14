#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // 이건 뭐지
#include <unistd.h> // 이것도 뭐지

int main(){
	// 1. 소켓 생성 - OS에게 TCP 연결 예약
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("소켓 생성됌 fd=%d\n", server_fd);

	// 2. 포트 등록
	struct sockaddr_in addr = {
		.sin_family = AF_INET, .sin_port = htons(8080), .sin_addr.s_addr = INADDR_ANY
	};
	bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
	printf("8080 포트바인딩 끗");

	// 3. 연결 대기
	listen(server_fd, 5);
	printf("연결 기다리는 중.. \n");

	// 4. 클라이언트 연결 수락
	int client_fd = accept(server_fd, NULL, NULL);
	printf("클라이언트 연결됌: fd=%d\n", client_fd);

	// 5. 응답
	char *response =
		 "HTTP/1.1 200 OK\r\n"
		"Content-Length: 12\r\n"
		"\r\n"
		"<h1>Hello world</h1>";
	send(client_fd, response, 13, 0);

	close(client_fd);
	close(server_fd);
	return 0;
}
