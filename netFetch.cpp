#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "netFetch.h"
#include <io.h>

bool _network = false;
char _netstate = _REQ_NONE;
char _netFinish = _REQ_NONE;
int _retval = 0;

char _msgBuff[4096];	// 4KB����ռ�
char _tmpDLFile[30];	// ��ʱ�����ļ���

vector<string> filelist;		// ���߻�ȡ���ļ��б�

// ��������������
SOCKADDR_IN server_Addr;
string _ipStr = "120.79.74.194";
short _Port = 5410;

// ������������
SOCKET Client_Sock;				// socket
int len = sizeof(SOCKADDR);		// ��ַ����

int DLL_init() {
	// ����socket��̬���ӿ�
	WORD wVersionRequested = MAKEWORD(2, 2);   // ����2.2�汾��WinSock��
	WSADATA wsaData;        // ����Windows Socket�Ľṹ��Ϣ
	DWORD err = WSAStartup(wVersionRequested, &wsaData);

	if (0 != err) {  // ����׽��ֿ��Ƿ�����ɹ�
		cerr << "Request Windows Socket Library Error.\n";
		system("pause");
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {  //����Ƿ�����������汾���׽��ֿ�
		WSACleanup();
		cerr << "Request Windows Socket Version 2.2 Error!\n";
		system("pasue");
		return -1;
	}
	return 1;
}

DWORD WINAPI _NetInit(LPVOID lp) {
_loop:
	Client_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Client_Sock == INVALID_SOCKET) {
		cout << "[SOCK ERROR] create socket failed." << endl;
		return false;
	}

	// �ӿڷ�������������
	memset((void*)&server_Addr, 0, len);//��ַ�ṹ��0����ʼ��Ϊ0

	server_Addr.sin_family = AF_INET;
	server_Addr.sin_addr.s_addr = inet_addr(_ipStr.c_str());
	server_Addr.sin_port = htons(_Port);

	int ret = connect(Client_Sock, (LPSOCKADDR)&server_Addr, sizeof(server_Addr));
	if (SOCKET_ERROR == ret) {
		closesocket(Client_Sock);
		Sleep(30 * 1000);
		goto _loop;
		// return false;
	}

	_network = true;
	char recvBuf[4096];
	ZeroMemory(_msgBuff, 0);

	while (1) {
		ZeroMemory(recvBuf, 0);
		int ret = recv(Client_Sock, recvBuf, 4096, 0);
		if (ret == SOCKET_ERROR || ret == 0) {
			_network = false;
			closesocket(Client_Sock);
			Sleep(1 * 1000);
			goto _loop;
		}
		recvBuf[ret] = '\0';
		

		// ����������ݴ���
		// cout << "Recv: " << recvBuf << endl;
		if (_netstate == _REQ_GL) {
			// memcpy(_msgBuff, recvBuf, 4096);
			int ret = _updFilelist(recvBuf);
			if (ret == 1) {
				// δ��ɴ��䣬���·���
			}
			else if (ret == 0) {
				// ���
				_netstate = _REQ_NONE;
				_netFinish = _REQ_GL;
			}
			else {
				// ʧ��
				filelist.clear();
				_netstate = _REQ_NONE;
			}
		}
		else if (_netstate == _REQ_DL) {
			memcpy(_msgBuff, recvBuf, 4096);
			_netstate = _REQ_NONE;
			_retval = _saveFile();
			if(_retval == 1)
				_netFinish = _REQ_DL;
			
		}
		else {

		}

		// _netstate = _REQ_NONE;
	}
}

bool _NetSendReq(char *s, char state) {
	if (!_network) {
		return false;
	}
	char msg[1024];
	fill(msg, msg + 1024, 0);
	if (state == _REQ_GL)	
		sprintf(msg, "{\"method\":\"GET\",\"idx\":%s}", s);
	else if (state == _REQ_DL) {
		fill(_tmpDLFile, _tmpDLFile + 30, 0);
		strcpy(_tmpDLFile, s);
		sprintf(msg, "{\"method\":\"POST\",\"idx\":\"%s\"}", s);
	}

	send(Client_Sock, msg, strlen(msg), 0);
	_netstate = state;
	return true;
}

int _saveFile() {
	char filepath[128];		// �����ļ��Ĵ洢·��
	
	// cout << dirPath << endl;
	sprintf(filepath, "%s\\download\\%s", dirPath, (char*)_tmpDLFile);
	// free(dirPath);
	// cout << modePath << endl;

	fill(_tmpDLFile, _tmpDLFile + 30, 0);
	printf("\n�������������ļ�,·��: %s. ", filepath);

	// �ж��ļ��Ƿ����
	if (_access(filepath, 0) == 0) 
		return -1;

	ofstream outfile;
	outfile.open(filepath);
	if (!outfile.is_open())
		return -2;

	// ��������\r\n�滻��\n
	string s(_msgBuff);
	int idx = 0;
	while (idx < s.length()) {
		idx = s.find("\r\n");
		if (idx == s.npos)
			break;
		s.replace(idx, 2, "\n");
	}
	outfile << s;
	outfile.close();
	return 1;
}

// ����ļ��б�
int _updFilelist(string s) {
	// cout << "_Upd: " << s << endl;
	if (s.find("END") != s.npos)
		return 0;	// ����
	if (s.find('#') == s.npos)
		return -1;	// ����
	stringstream ss(s);
	string str;
	while (getline(ss, str, '#')) {
		filelist.push_back(str);
	}
	return 1;		// ���
}

bool _swapFile(vector<string>& list) {
	if (_netFinish == _REQ_GL) {
		list.clear();
		list.swap(filelist);
		return true;
	}
	else return false;
}