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
	sockaddr_in socketAddress;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.S_un.S_addr = INADDR_ANY;
	socketAddress.sin_port = htons(0);



	bind(handle, (sockaddr*)&socketAddress, sizeof(sockaddr_in));

	DWORD param = 1;
	ioctlsocket(handle, FIONBIO, &param);
	
	// preparing to send
	sockaddr_in outAddress,inAddress;	// inaddress will be automatically populated w/ the address of whomever you get a message from
	outAddress = nsfw::stoa("10.15.22.49:50000");
	//outAddress = nsfw::stoa("127.0.0.1:50000");
	//tyler 88
	//esme 54
	//jared 61
	int in_len = sizeof(sockaddr_in);
	char outBuffer[256] = "ABC";
	char inBuffer[256];

	// sending

	while (true)
	{
		int sent = sendto(handle, outBuffer, 256, 0, (sockaddr*)&outAddress, sizeof(sockaddr_in));
		int recv = recvfrom(handle, inBuffer, 256, 0, (sockaddr*)&inAddress, &in_len);
		std::cout << inBuffer << "\n";
	}


	
	

	system("pause");

	closesocket(handle);
	nsfw::termNetworking();
	

}