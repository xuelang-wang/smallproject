// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET serversoc;
	SOCKET clientsoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	int len;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL


	//创建套接字
	if ((serversoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("套接字socket创建失败!\n");
		return -1;
	}

	//命名协议，IP，端口
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9101);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	len = sizeof(SOCKADDR_IN);

	//绑定套接字
	if (bind(serversoc, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("套接字绑定失败!\n");
		return -1;
	}

	printf("开始监听...\n");
	//监听请求
	if (listen(serversoc, 1) != 0)
	{
		printf("监听失败!\n");
		return -1;
	}

	//接收请求
	if ((clientsoc = accept(serversoc, (SOCKADDR *)&clientaddr, &len)) <= 0)
	{
		printf("接受连接失败!\n");
		return -1;
	}
	printf("连接成功\n");

	while (1){
		//接收数据
		while (1)
		{
			if (recv(clientsoc, buf, 1024, 0) <= 0)
			{
				printf("关闭连接!\n");
				closesocket(clientsoc);
			}

			if (buf[0] == 'N')
				break;

			printf("接收来自客户端的信息: %s\n", buf);
			break;
		}

		if (buf[0] == 'N')
			break;

		//发送数据
		printf("请输入发送给客户端的字符(N表示结束):\n");
		scanf_s("%s", buf, 1024);
		//send to client
		if (send(clientsoc, buf, strlen(buf) + 1, 0) <= 0)
		{
			printf("发送错误!\n");
		}

		if (buf[0] == 'N')
			break;
	}
	WSACleanup();     //释放WS2_32.DLL

	return 0;
}

