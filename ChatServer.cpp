#include "ChatServer.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

ChatServer::ChatServer() :
	serverPort_(8888), messageLength_(1024),
	sock_()
{
}

ChatServer::ChatServer(unsigned short port) :
	serverPort_(port), messageLength_(1024),
	sock_()
{
}

ChatServer::ChatServer(unsigned short port, unsigned int length) :
	serverPort_(port), messageLength_(length),
	sock_()
{
}

ChatServer::~ChatServer() {
}

bool ChatServer::InitWinSock() {
	//WinSock�{��
	WSADATA wsaData;

	//������
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	return (ret != 0);
}

bool ChatServer::InitSocket() {
	sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	return (sock_ == INVALID_SOCKET);
}

bool ChatServer::SetServerIP() {
	//�\�P�b�g�Ƀ|�[�g�����i�[
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bindAddr.sin_port = htons(serverPort_);

	return(bind(sock_, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR);
}

bool ChatServer::Loop() {
	//���C�����[�v
	while (true) {
		///// ���b�Z�[�W��M /////
		//����l���T�[�o�ƍ��킹��
		char* buff = new char[messageLength_];	//���p�o�b�t�@

		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		if (recvfrom(sock_, buff, messageLength_, 0, (SOCKADDR*)&fromAddr, &fromlen) == SOCKET_ERROR) {
			cout << "Error : Recieve Message" << endl;
			delete[] buff;
			return false;
		}
		else {
			//�\��
			cout << "Receive Message : " << buff << endl;
			delete[] buff;
		}

		///// ���b�Z�[�W���M /////
		//char message[];	//���b�Z�[�W
		//std::cout << "Input Message : ";
		//cin >> message;
		string message;
		message.resize(messageLength_);//����l���T�[�o�ƍ��킹��
		std::cout << "Input Message : ";
		cin >> message;
		//std::getline(cin, message);

		if (sendto(sock_, message.c_str(), messageLength_, 0, (SOCKADDR*)&fromAddr, fromlen) == SOCKET_ERROR) {
			cout << "Error : sendto" << endl;
			return false;
		}
		string tmp = "";
		cout << "Want to Close Connection? (Y / N) : ";
		cin >> tmp;
		if (tmp == "Y") {
			cout << "Now Closing Connection..." << endl;
			break;
		}
	}
	return true;
}

bool ChatServer::ReleaseSocket() {
	return (closesocket(sock_) == SOCKET_ERROR);
}

bool ChatServer::ReleaseWinSock() {
	return (WSACleanup() != 0);
}
