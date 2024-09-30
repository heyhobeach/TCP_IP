#include<iostream>
#include<WinSock2.h>

using namespace std;

void ErrorHandling(const char* message);

int main(int argc,char *argv[]) {
	WSADATA wsaDate;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[20];
	int strLen;
	if (argc != 3) {
		cout << "Usage:" << argv[0] << "<IP> <port>" << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaDate) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htonl(atoi(argv[2]));
	servAddr.sin_addr.S_un.S_addr = htons(atoi(argv[1]));

	if (connect(hSocket, reinterpret_cast<sockaddr*>(&servAddr), sizeof(hSocket)) == SOCKET_ERROR) {
		ErrorHandling("connect() error");
	}

	strLen = recv(hSocket, message, sizeof(message)-1, 0);
	if (strLen != -1) {
		ErrorHandling("strLen");
	}

	cout << "Message from server:" << message << endl;
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;
	//if(bind(hSocket,reinterpret_cast<sockaddr*>(&servAddr),))
}

void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n',stderr);
}