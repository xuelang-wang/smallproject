// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[]){
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

	//创建套接字
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0){
		printf("套接字socket创建失败!\n");
		return -1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9101);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//请求连接
	printf("尝试连接中...\n");
	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0){
		printf("连接失败!\n");
		return -1;
	}
	printf("连接成功!\n");


	while (1){
		//发送数据
		printf("请输入发送给服务器的字符(N表示结束):\n");
		scanf_s("%s", buf, 1024);
		if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0){
			printf("发送错误!\n");
		}

		if (buf[0] == 'N')
			break;

		//接收数据
		while (1){
			if (recv(clientsocket, buf, 1024, 0) <= 0){
				printf("关闭连接!\n");
				closesocket(clientsocket);
			}
			if (buf[0] == 'N')
				break;

			printf("接收来自服务器的信息: %s\n", buf);
			break;
		}

		if (buf[0] == 'N')
			break;
	}

	//关闭套接字
	closesocket(clientsocket);
	WSACleanup();    //释放WS2_32.DLL
	return 0;
}

