#include <iostream>
#include "ChatServer.h"

using std::cout;
using std::endl;

int main() {
	ChatServer* pServer = new ChatServer();

	//WinSockの初期化
	if (pServer->InitWinSock()) {
		cout << "Error : WSAStartUp" << endl;
		delete pServer;
		return -1;
	}
	cout << "Success : WinSock StartUp" << endl;

	//ソケット作成
	if (pServer->InitSocket()) {
		cout << "Error : Create Socket" << endl;
		delete pServer;
		return -1;
	}
	cout << "Success : Create Socket" << endl;

	
	if (pServer->SetServerIP()) {
		cout << "Error : Bind Socket" << endl;
		return -1;
	}
	cout << "Success : Bind Socket" << endl;

	cout << "Now Connecting..." << endl;
	cout << "Server opens now! Let's Communicate with Others!" << endl;
	
	//メインループ
	if (!(pServer->Loop())) {
		cout << "Error : Connection Failer" << endl;
	}
	else {
		cout << "Success : Connection is Closed" << endl;
	}

	//ソケットの後処理
	if (pServer->ReleaseSocket()) {
		cout << "Error : closesocket" << endl;
		delete pServer;
		return -1;
	}

	//WinSockの後処理
	if (pServer->ReleaseWinSock()) {
		cout << "Error : WSACleanup" << endl;
		delete pServer;
		return -1;
	}

	delete pServer;
	return 0;
}