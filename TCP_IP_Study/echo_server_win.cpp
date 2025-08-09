#include<iostream>
#include<string>
#include<stdlib.h>
#include<WinSock2.h>


const int MAXLENGTH = 1024;
using namespace std;
string error_function(const char* message) {
	fputs(message, stderr);//cerr와 차이가 뭔지가 모름
	fputc('\n', stderr);
	exit(1);//return 1 이나 return 0 와 차이는?
}

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET hServSock, hClntSock;
	char message[MAXLENGTH];
	int strLen;

	SOCKADDR_IN servAddr, clntAddr;
	int clntAdrSize;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		error_function("wsastartup error");
	}

	hServSock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)(&servAddr), sizeof(servAddr)) == SOCKET_ERROR) {
		error_function("bind error");
	}

	if (listen(hServSock, 5) == SOCKET_ERROR) {
		error_function("listen error");
	}

	clntAdrSize = sizeof(clntAddr);

	for (int i = 0; i < 5; i++) {
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAdrSize);
		if (hClntSock == -1) {
			error_function("accept() error");
		}
		else {
			printf("connect");
		}

		while ((strLen = recv(hClntSock, message, MAXLENGTH, 0)) != 0) {
			send(hClntSock, message, strLen, 0);
		}

		closesocket(hClntSock);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;

}