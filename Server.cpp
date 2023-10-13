/*
WSAStartup()	// WinSock������
socket()		// �\�P�b�g�쐬
bind()			// �\�P�b�g�A�h���X���̊��蓖��
while(true)
{
	recvfrom()		// ��M
	�o��
	���M���b�Z�[�W����
sendto()		// ���M
}
closesocket()		// �\�P�b�g�j��
WSACleanup()		// WinSock�I������
*/

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::cout;
using std::endl;

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;

// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

// �v���g�^�C�v�錾
int InitWinSock();

int main()
{
	cout << "You are Chat Server" << endl;

	//�������̌��ʂ��i�[����ϐ�
	int ret;

	// WinSock�̏�����
	ret = InitWinSock();
	if (ret != 0) {
		cout << "WinSock Initializing Error";
		return -1;
	}
	cout << "Initialize WinSock is Success" << endl;

	// �\�P�b�g�f�B�X�N���v�^
	SOCKET sock;

	// UDP�\�P�b�g�쐬
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		cout << "Socket Creation Error" << endl;
		return -1;
	}
	cout << "Create Socket is Success" << endl;

	// �\�P�b�g�Ɏg�p����|�[�g�ԍ���ݒ�
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bindAddr.sin_port = htons(SERVERPORT);

	ret = bind(sock, (SOCKADDR*)&bindAddr, sizeof(bindAddr));
	if (ret == SOCKET_ERROR) {
		cout << "IP address Bind Error" << endl;
		return -1;
	}
	cout << "Binding IP address is Success" << endl;

	cout << "\nYour IP Address is " << bindAddr.sin_addr.s_addr << endl;

	// ���[�v
	while (false)
	{
		char buff[MESSAGELENGTH];
		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		ret = recvfrom(sock, buff, MESSAGELENGTH, 0, (SOCKADDR*)&fromAddr, &fromlen);
		if (ret == SOCKET_ERROR)
		{
			/*
				�G���[����
			*/
		}
		else
		{
			std::cout << buff << std::endl;
		}
	}


	// �����܂ł��Ȃ����ǁA�\�P�b�g�j��
	ret = closesocket(sock);
	if (ret == SOCKET_ERROR)
	{
		/*
			�G���[����
		*/
	}

	// WinSock�̏I������
	ret = WSACleanup();
	if (ret == SOCKET_ERROR)
	{
		/*
			�G���[����
		*/
	}


	return 0;
}

int InitWinSock() {
	//WinSock��\���\����
	WSADATA wsaData;
	// WinSock�̏�����  WinSock2.2
	return(WSAStartup(MAKEWORD(2, 2), &wsaData));
}