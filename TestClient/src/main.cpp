#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include <WS2tcpip.h>
#include<WinSock2.h>
using namespace std;
// #pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA wsa;
	SOCKET serversoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN peeraddr;
	int peer_len = sizeof(peeraddr);
	char Recv_buf[64];
	char send_con[] = "Hello, server!";
	char* Send_data = send_con;
	int Send_len = strlen(Send_data);
	int time_out = 2000;    
	int result;
	WORD sockVersion = MAKEWORD(2,2);

	WSAStartup(sockVersion, &wsa);	

	//define protocol, IP, port
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(13);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	if (serveraddr.sin_addr.s_addr == INADDR_NONE)
	{
		printf("invalid address!!\n");
		return -1;
	}
	printf("okay!\n");
	//create socket
	serversoc = socket(AF_INET, SOCK_DGRAM, 0);

	result = setsockopt(serversoc, SOL_SOCKET, SO_RCVTIMEO, (char*)& time_out, sizeof(time_out));
	for (int i = 0; i < 3; i++)
	{
		//send
		result = sendto(serversoc, Send_data, Send_len, 0, (SOCKADDR*)& serveraddr, sizeof(serveraddr));
		//receive
		result = recvfrom(serversoc, Recv_buf, 64, 0, (SOCKADDR*)& peeraddr, &peer_len);
		if (result >= 0)
		{
			Recv_buf[result] = 0;
			printf("Received data from server:  %s \n", Recv_buf);
		}
	}
	closesocket(serversoc);
	WSACleanup();
	return 0;
}
