#pragma once
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <direct.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

//GL {"method":"GET","idx":0}
//DL {"method":"POST", "file":"filename"}


#define _REQ_NONE	0x00	// ������
#define _REQ_GL		0x01	// ��ȡ�ļ��б�
#define _REQ_DL		0x02	// �����ļ�

extern bool _network;		// ����״̬
extern char _netstate;		// ����״̬
extern char _netFinish;		// �������״̬
extern int _retval;			// ����ֵ
extern char _msgBuff[4096];	// ����ռ�
extern char* dirPath;		// Ŀ¼·��

int DLL_init();							// ���ض�̬��
DWORD WINAPI _NetInit(LPVOID lp);		// ��ʼ������
bool _NetSendReq(char *s, char state);	// ���������߳�
int _saveFile();						// �����ļ�
int _updFilelist(string s);				// ��ȡ�����ļ��б�
bool _swapFile(vector<string> &list);	// �����ļ��б�
