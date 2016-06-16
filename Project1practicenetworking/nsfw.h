#pragma once
#pragma comment (lib, "wininet")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

namespace nsfw
{
	bool initNetworking()
	{
		WSAData data;
		return WSAStartup(MAKEWORD(2, 2), &data) == 0;
	}
	bool termNetworking()
	{
		return WSACleanup() == NO_ERROR;
	}

	//create a function to convert a string to an address
	sockaddr_in stoa(const char* src)
	{
		sockaddr_in dst;
		dst.sin_family = AF_INET;
		int first = -1;
		int second = -1;
		int third = -1;
		int fourth = -1;
		int port = -1;
		
		sscanf_s(src, "%d.%d.%d.%d:%d", &first, &second, &third, &fourth, &port);
		// figure out the IP address
		// figure out the port


		dst.sin_addr.S_un.S_un_b.s_b1 = first;
		dst.sin_addr.S_un.S_un_b.s_b2 = second;
		dst.sin_addr.S_un.S_un_b.s_b3 = third;
		dst.sin_addr.S_un.S_un_b.s_b4 = fourth;
		dst.sin_port = htons(port);

		return dst;
	}
}
