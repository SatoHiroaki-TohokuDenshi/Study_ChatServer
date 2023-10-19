#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using std::string;

class ChatServer {
private:
	unsigned short serverPort_;		//�|�[�g�ԍ�
	unsigned int messageLength_;	//�ő啶����

	SOCKET sock_;

	string serverIP_;
	SOCKADDR_IN toAddr_;
	int tolen_;
public:
	ChatServer();
	ChatServer(unsigned short port);
	ChatServer(unsigned short port, unsigned int length);
	~ChatServer();

	///// ������ /////
	bool InitWinSock();
	bool InitSocket();
	bool SetServerIP();

	///// ���C�����[�v /////
	bool Loop();

	///// ��� /////
	bool ReleaseSocket();
	bool ReleaseWinSock();
};