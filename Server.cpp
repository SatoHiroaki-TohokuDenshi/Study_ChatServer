/*
WSAStartup()	// WinSock初期化
socket()		// ソケット作成
bind()			// ソケットアドレス情報の割り当て
while(true)
{
	recvfrom()		// 受信
	出力
	送信メッセージ入力
sendto()		// 送信
}
closesocket()		// ソケット破棄
WSACleanup()		// WinSock終了処理
*/

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::cout;
using std::endl;

// ポート番号
const unsigned short SERVERPORT = 8888;

// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

// プロトタイプ宣言
int InitWinSock();

int main()
{
	cout << "You are Chat Server" << endl;

	//初期化の結果を格納する変数
	int ret;

	// WinSockの初期化
	ret = InitWinSock();
	if (ret != 0) {
		cout << "WinSock Initializing Error";
		return -1;
	}
	cout << "Initialize WinSock is Success" << endl;

	// ソケットディスクリプタ
	SOCKET sock;

	// UDPソケット作成
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		cout << "Socket Creation Error" << endl;
		return -1;
	}
	cout << "Create Socket is Success" << endl;

	// ソケットに使用するポート番号を設定
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

	// ループ
	while (false)
	{
		char buff[MESSAGELENGTH];
		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		ret = recvfrom(sock, buff, MESSAGELENGTH, 0, (SOCKADDR*)&fromAddr, &fromlen);
		if (ret == SOCKET_ERROR)
		{
			/*
				エラー処理
			*/
		}
		else
		{
			std::cout << buff << std::endl;
		}
	}


	// ここまでこないけど、ソケット破棄
	ret = closesocket(sock);
	if (ret == SOCKET_ERROR)
	{
		/*
			エラー処理
		*/
	}

	// WinSockの終了処理
	ret = WSACleanup();
	if (ret == SOCKET_ERROR)
	{
		/*
			エラー処理
		*/
	}


	return 0;
}

int InitWinSock() {
	//WinSockを表す構造体
	WSADATA wsaData;
	// WinSockの初期化  WinSock2.2
	return(WSAStartup(MAKEWORD(2, 2), &wsaData));
}