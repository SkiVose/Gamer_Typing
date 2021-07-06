#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

struct CountBoard {
	int cur;		// ��ǰλ��
	int total;		// ����
	int right;		// �����
	int wrong;		// �����
	int checked;	// �����
	int uncheck;	// ������
	bool *chkArray;	// ������
};

struct wNode {
	char word[128];			// ԭ��
	char anno[1792];		// ע��
	char Userword[128];		// �û�ƴд
};	// 2KB

vector<wNode*> strArray;
vector<string> olList;	

bool ReadCsvdata(char* path);
bool PrintWords();
bool getFiles(char* path, vector<string>& vfiles, bool slient);
bool mainPage();
bool localPage(char* mPath);
bool onlinePage();
void TypingPage(); 
void PrintHeader(string str, CountBoard* cb);
void FinishType(CountBoard* cb);
bool CheckSpell(string str, CountBoard* cb);