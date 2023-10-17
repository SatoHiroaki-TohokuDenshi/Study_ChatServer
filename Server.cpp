#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

///// �萔�錾 /////
const unsigned short SERVER_PORT = 8888;	//�|�[�g�ԍ�
const unsigned int MESSAGE_LENGTH = 1024;	//����M�̍ő啶����

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	//���ʊi�[�p�ϐ�
	int result = 0;

	//WinSock�{��
	WSADATA wsaData;

	//������
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Error : WinSock StartUp" << endl;
		return -1;
	}
	cout << "Success : WinSock StartUp" << endl;

	//�\�P�b�g�f�B�X�N���v�^
	SOCKET sock;

	//UDP�\�P�b�g�쐬
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		cout << "Error : Create Socket" << endl;
		return -1;
	}

	cout << "Success : Create Socket" << endl;

	//�\�P�b�g�Ƀ|�[�g�����i�[
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bindAddr.sin_port = htons(SERVER_PORT);

	result = bind(sock, (SOCKADDR*)&bindAddr, sizeof(bindAddr));
	if (result == SOCKET_ERROR) {
		cout << "Error : Bind Socket" << endl;
		return -1;
	}
	cout << "Success : Bind Socket" << endl;

	cout << "Now Connecting..." << endl;
	cout << "Server opens now! Let's Communicate with Others!" << endl;
	//���C�����[�v
	while (true) {
		///// ���b�Z�[�W��M /////
		//����l���T�[�o�ƍ��킹��
		char buff[MESSAGE_LENGTH];	//���p�o�b�t�@

		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		result = recvfrom(sock, buff, MESSAGE_LENGTH, 0, (SOCKADDR*)&fromAddr, &fromlen);
		if (result == SOCKET_ERROR) {
			cout << "Error : Recieve Message" << endl;
			return -1;
		}
		else {
			//�\��
			cout << "Receive Message : " << buff << endl;
		}

		///// ���b�Z�[�W���M /////
		//string message;
		//message.resize(MESSAGE_LENGTH);//����l���T�[�o�ƍ��킹��
		//std::cout << "Input Message : ";
		//std::getline(cin, message);
		char message[MESSAGE_LENGTH];	//���b�Z�[�W
		std::cout << "Input Message : ";
		cin >> message;

		result = sendto(sock, message, MESSAGE_LENGTH, 0, (SOCKADDR*)&fromAddr, fromlen);
		if (result == SOCKET_ERROR) {
			cout << "Error : Message Sending" << endl;
			return -1;
		}
	}

	//�\�P�b�g�̌㏈��
	result = closesocket(sock);
	if (result == SOCKET_ERROR) {
		cout << "Error : closesocket" << endl;
		return -1;
	}

	//WinSock�̌㏈��
	result = WSACleanup();
	if (result != 0) {
		cout << "Error : WSACleanup" << endl;
		return -1;
	}

	return 0;
}

//WSAStartup()	// WinSock������
//socket()		// �\�P�b�g�쐬
///*
//	�T�[�o�̃\�P�b�g�A�h���X�����Z�b�g
//*/
//while (true)
//{
//	/*
//		���M���b�Z�[�W����
//	*/
//	sendto();	// ���M
//	recvfrom();	// ��M
//	/*
//	�o��
//	*/
//}
//closesocket()		// �\�P�b�g�j��
//WSACleanup()		// WinSock�I������