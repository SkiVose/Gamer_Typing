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


#define _REQ_NONE	0x00	// 无任务
#define _REQ_GL		0x01	// 获取文件列表
#define _REQ_DL		0x02	// 下载文件

extern bool _network;		// 网络状态
extern char _netstate;		// 网络活动状态
extern char _netFinish;		// 网络活动完成状态
extern int _retval;			// 返回值
extern char _msgBuff[4096];	// 共享空间
extern char* dirPath;		// 目录路径

int DLL_init();							// 加载动态库
DWORD WINAPI _NetInit(LPVOID lp);		// 初始化网络
bool _NetSendReq(char *s, char state);	// 发送请求线程
int _saveFile();						// 保存文件
int _updFilelist(string s);				// 获取线上文件列表
bool _swapFile(vector<string> &list);	// 交换文件列表
