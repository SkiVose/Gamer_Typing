#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

struct CountBoard {
	int cur;		// 当前位置
	int total;		// 总数
	int right;		// 答对数
	int wrong;		// 答错数
	int checked;	// 完成数
	int uncheck;	// 待做数
	bool *chkArray;	// 检查矩阵
};

struct wNode {
	char word[128];			// 原词
	char anno[1792];		// 注释
	char Userword[128];		// 用户拼写
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