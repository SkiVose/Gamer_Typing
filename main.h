#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

#define _WB_1	0x00		// �ڵװ���
#define _WB_2	0x01		// ���װ���
#define _WY		0x02		// �Ƶװ���
#define _WG		0x03		// �̵װ���
#define _WC		0x04		// ��װ���
#define _WR		0x05		// ��װ���
#define _WP		0x06		// �۵װ���

// #define _BW_1	0x10		// �׵׺���
#define _BB		0x10		// �ڵ�����
#define _YB		0x20		// �ڵ׻���
#define _GB		0x30		// �ڵ�����
#define _CB		0x40		// �ڵ�����
#define _RB		0x50		// �ڵ׺���
#define _PB		0x60		// �ڵ׷���

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

void CC(char cs);
bool ReadCsvdata(char* path);
bool PrintWords();
bool getFiles(char* path);
bool ChoosePage(char* path);
void TypingPage(); 
void PrintHeader(string str, CountBoard* cb);
void FinishType(CountBoard* cb);
bool CheckSpell(string str, CountBoard* cb);