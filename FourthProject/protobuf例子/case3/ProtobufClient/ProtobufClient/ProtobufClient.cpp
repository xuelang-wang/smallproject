// ProtobufClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

google::protobuf::uint32 readHdr(char *buf);
void readBody(int csock, google::protobuf::uint32 siz);
void* SocketHandler(SOCKET &csock);


int _tmain(int argc, _TCHAR* argv[]){
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	//char buf[1024];

	log_packet payload;
	int siz;
	char *buf;


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
		int id;
		string str;
		cout << "Enter id : ";
		cin >> id;
		cout << "Enter str : ";
		cin >> str;
		payload.set_id(id);
		payload.set_str(str);

		siz = payload.ByteSize() + 4;
		buf = new char[siz];

		google::protobuf::io::ArrayOutputStream aos(buf, siz);
		CodedOutputStream *coded_output = new CodedOutputStream(&aos);
		coded_output->WriteVarint32(payload.ByteSize());
		payload.SerializeToCodedStream(coded_output);

		if (send(clientsocket, buf, siz, 0) <= 0){
			printf("发送错误!\n");
		}

		//接收数据
		SocketHandler(clientsocket);
	}

	//关闭套接字
	closesocket(clientsocket);
	WSACleanup();    //释放WS2_32.DLL
	return 0;
}

google::protobuf::uint32 readHdr(char *buf)
{
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf, 4);
	CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size);//Decode the HDR and get the size
	//cout << "size of payload is " << size << endl;
	return size;
}

void readBody(int csock, google::protobuf::uint32 siz)
{
	int bytecount;
	log_packet payload;
	char *buffer = new char[siz + 4];//size of the payload and hdr
	//Read the entire buffer including the hdr
	if ((bytecount = recv(csock, buffer, 4 + siz, MSG_WAITALL)) == -1){
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	//cout << "Second read byte count is " << bytecount << endl;
	//Assign ArrayInputStream with enough memory 
	google::protobuf::io::ArrayInputStream ais(buffer, siz + 4);
	CodedInputStream coded_input(&ais);
	//Read an unsigned integer with Varint encoding, truncating to 32 bits.
	coded_input.ReadVarint32(&siz);
	//After the message's length is read, PushLimit() is used to prevent the CodedInputStream 
	//from reading beyond that length.Limits are used when parsing length-delimited 
	//embedded messages
	google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
	//De-Serialize
	payload.ParseFromCodedStream(&coded_input);
	//Once the embedded message has been parsed, PopLimit() is called to undo the limit
	coded_input.PopLimit(msgLimit);
	
	//打印当前时间
	time_t curtime;
	time(&curtime);
	char   pblgtime[20];
	strftime(pblgtime, 20, "%Y-%m-%d %X", localtime(&curtime));
	cout << pblgtime << endl;
	
	//Print the message
	cout << "Server message is \n" << payload.DebugString();
}

void* SocketHandler(SOCKET &csock){

	char buffer[4];
	int bytecount = 0;
	string output, pl;
	log_packet logp;

	memset(buffer, '\0', 4);


	//Peek into the socket and get the packet size
	if ((bytecount = recv(csock,
		buffer,
		4, MSG_PEEK)) == -1){
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	//cout << "First read byte count is " << bytecount << endl;
	readBody(csock, readHdr(buffer));

	return NULL;
}
