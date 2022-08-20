#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA d;
	WORD w = MAKEWORD(2, 0);
	WSAStartup(w, &d);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(9999);

	int len = sizeof(serverAddr);

	char buf[] = "Hello, UDP server!";

	int ret = sendto(s, buf, sizeof(buf), 0, (sockaddr*)&serverAddr, len);

	cout << "ret == " << ret << endl;

	char recvBuf[512] = { 0 };
	int recvLen = recvfrom(s, recvBuf, 512, 0, (sockaddr*)&serverAddr, &len);
	if (recvLen > 0) {
		cout << recvBuf << endl;
	}
	else {
		cout << "nothing" << endl;
	}
	
	getchar();
	closesocket(s);
	WSACleanup();
	return 0;
}