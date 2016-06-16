#pragma comment (lib, "wininet")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "nsfw.h"

int main() 
{
	// init
	if (!nsfw::initNetworking())
	{
		exit(0);
	}
	
	// creating the socket
	int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in socketAddress = nsfw::stoa("127.0.0.1:50000");

	bind(handle, (sockaddr*)&socketAddress, sizeof(sockaddr_in));

	DWORD param = 1;
	ioctlsocket(handle, FIONBIO, &param);
	
	// preparing to send
	sockaddr_in outAddress,inAddress;	// inaddress will be automatically populated w/ the address of whomever you get a message from
	outAddress = nsfw::stoa("10.15.22.54:50000");
	//tyler 88
	//esme 54
	int in_len = sizeof(sockaddr_in);
	char outBuffer[40] = "||||";
	char inBuffer[40];

	// sending

	while (true)
	{
		sendto(handle, outBuffer, 40, 0, (sockaddr*)&outAddress, sizeof(sockaddr_in));
		recvfrom(handle, inBuffer, 40, 0, (sockaddr*)&inAddress, &in_len);
	}
	
	
	
	std::cout << inBuffer << "\n";

	closesocket(handle);
	nsfw::termNetworking();
	system("pause");

}