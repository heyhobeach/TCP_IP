#include<iostream>
#include<string>
#include<WinSock2.h>

void ErrorHangling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
}

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHangling("WSAStartup() Error");
	}

	//inet_addr 방식
	{
		const char* addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);
		if (conv_addr == INADDR_NONE) {
			std::cout << "Error occured!\n";
		}
		else {
			std::cout << "Network ordered integer addr :0x" << std::hex << conv_addr << '\n';
		}
	}

	//inet_ntoa 방식
	{
		sockaddr_in addr;
		char* strPtr;
		char strArr[20];

		addr.sin_addr.s_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		std::cout << "Dotted-Decimal notation3" << strArr<<'\n';
	}

	WSACleanup();
	return 0;
}