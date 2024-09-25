#include <iostream>
#include <WinSock2.h>

using namespace std;
void ErrorHandling(char* message);

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

	return 0;
}