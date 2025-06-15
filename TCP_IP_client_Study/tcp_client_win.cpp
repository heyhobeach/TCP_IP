#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>

using namespace std;

void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
}

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET hsock;
	SOCKADDR_IN servAddr;

	char message[100];
	int strlen = 0;
	int idx = 0, read_len = 0;

	if (argc != 3) {
		cout << "Usage :" << argv[0] << "<IP> <port>\n";
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup error");
	}
	hsock = socket(PF_INET, SOCK_STREAM, 0);

	if (hsock == INVALID_SOCKET) {
		ErrorHandling("hSockError");
	}

	memset(&servAddr, 0, sizeof(servAddr));

	//servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	//servAddr.sin_port = htons(atoi(argv[2]));

	servAddr.sin_family = AF_INET;

	//아래 과정은 ip주소 매칭 하는 sinaddr.s_addr을 안 쓸 경우임
	wchar_t waddr[INET6_ADDRSTRLEN];
	if (MultiByteToWideChar(CP_ACP, 0, argv[1], -1,waddr, INET6_ADDRSTRLEN) == 0) {
		ErrorHandling("multibytetoWiderChar");
	}

	InetPtonW(AF_INET, waddr, &servAddr.sin_addr);
	servAddr.sin_port = htons(atoi(argv[2]));
	if (connect(hsock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("connect error");
	}

	while (read_len = recv(hsock, &message[idx++], 1, 0)) {
		if (read_len == -1) {
			ErrorHandling("recv error");
		}
		strlen += read_len;
	}

	cout << "Message from server " << message << endl;
	cout << "Function read call cout" << strlen << endl;

	closesocket(hsock);
	WSACleanup();



}