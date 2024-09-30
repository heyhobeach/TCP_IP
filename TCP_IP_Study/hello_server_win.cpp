#include <iostream>
#include <WinSock2.h>

using namespace std;
void ErrorHandling(const char* message);

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET hServerSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[] = "Hello World!";
	if (argc != 2) {
		cout << "Usage:" << argv[0] << "<port>" << endl;
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartupError");
	}
	hServerSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServerSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//S_un.s_addr = s_addr
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServerSock, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr) == SOCKET_ERROR) ){
		ErrorHandling("bind() error");
	}

	if (listen(hServerSock, 5) == INVALID_SOCKET) {
		ErrorHandling("listen() error");
	}
	szClntAddr =sizeof(clntAddr);
	hClntSock = accept(hServerSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET) {
		ErrorHandling("accept() error");
	}

	send(hClntSock, message, sizeof(message), 0);
	closesocket(hClntSock);
	closesocket(hServerSock);
	WSACleanup();

	return 0;

}

void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
}