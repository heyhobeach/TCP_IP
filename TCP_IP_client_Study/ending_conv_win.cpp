#include<iostream>
#include<winsock2.h>

void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
}

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	std::cout << "Host ordered port :0x" << std::hex<<host_port << '\n';
	std::cout << "NetWork ordered port :0x" << std::hex << net_port << '\n';
	std::cout << "Host ordered address :0x" << std::hex << host_addr << '\n';
	std::cout << "Host ordered address :0x" << std::hex << net_addr << '\n';

	WSACleanup();
	return 0;
}