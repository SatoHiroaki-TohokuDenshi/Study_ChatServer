#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

///// 定数宣言 /////
const unsigned short SERVER_PORT = 8888;	//ポート番号
const unsigned int MESSAGE_LENGTH = 1024;	//送受信の最大文字数

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	//結果格納用変数
	int result = 0;

	//WinSock本体
	WSADATA wsaData;

	//初期化
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Error : WinSock StartUp" << endl;
		return -1;
	}
	cout << "Success : WinSock StartUp" << endl;

	//ソケットディスクリプタ
	SOCKET sock;

	//UDPソケット作成
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		cout << "Error : Create Socket" << endl;
		return -1;
	}

	cout << "Success : Create Socket" << endl;

	//ソケットにポート情報を格納
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
	//メインループ
	while (true) {
		///// メッセージ受信 /////
		//上限値をサーバと合わせる
		char buff[MESSAGE_LENGTH];	//受取用バッファ

		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		result = recvfrom(sock, buff, MESSAGE_LENGTH, 0, (SOCKADDR*)&fromAddr, &fromlen);
		if (result == SOCKET_ERROR) {
			cout << "Error : Recieve Message" << endl;
			return -1;
		}
		else {
			//表示
			cout << "Receive Message : " << buff << endl;
		}

		///// メッセージ送信 /////
		//string message;
		//message.resize(MESSAGE_LENGTH);//上限値をサーバと合わせる
		//std::cout << "Input Message : ";
		//std::getline(cin, message);
		char message[MESSAGE_LENGTH];	//メッセージ
		std::cout << "Input Message : ";
		cin >> message;

		result = sendto(sock, message, MESSAGE_LENGTH, 0, (SOCKADDR*)&fromAddr, fromlen);
		if (result == SOCKET_ERROR) {
			cout << "Error : Message Sending" << endl;
			return -1;
		}
	}

	//ソケットの後処理
	result = closesocket(sock);
	if (result == SOCKET_ERROR) {
		cout << "Error : closesocket" << endl;
		return -1;
	}

	//WinSockの後処理
	result = WSACleanup();
	if (result != 0) {
		cout << "Error : WSACleanup" << endl;
		return -1;
	}

	return 0;
}

//WSAStartup()	// WinSock初期化
//socket()		// ソケット作成
///*
//	サーバのソケットアドレス情報をセット
//*/
//while (true)
//{
//	/*
//		送信メッセージ入力
//	*/
//	sendto();	// 送信
//	recvfrom();	// 受信
//	/*
//	出力
//	*/
//}
//closesocket()		// ソケット破棄
//WSACleanup()		// WinSock終了処理