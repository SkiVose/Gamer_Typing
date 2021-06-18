#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

#define _WB_1	0x00		// ºÚµ×°××Ö
#define _WB_2	0x01		// À¶µ×°××Ö
#define _WY		0x02		// »Æµ×°××Ö
#define _WG		0x03		// ÂÌµ×°××Ö
#define _WC		0x04		// Çàµ×°××Ö
#define _WR		0x05		// ºìµ×°××Ö
#define _WP		0x06		// ·Ûµ×°××Ö

// #define _BW_1	0x10		// °×µ×ºÚ×Ö
#define _BB		0x10		// ºÚµ×À¶×Ö
#define _YB		0x20		// ºÚµ×»Æ×Ö
#define _GB		0x30		// ºÚµ×ÂÌ×Ö
#define _CB		0x40		// ºÚµ×Çà×Ö
#define _RB		0x50		// ºÚµ×ºì×Ö
#define _PB		0x60		// ºÚµ×·Û×Ö

struct CountBoard {
	int cur;		// µ±Ç°Î»ÖÃ
	int total;		// ×ÜÊý
	int right;		// ´ð¶ÔÊý
	int wrong;		// ´ð´íÊý
	int checked;	// Íê³ÉÊý
	int uncheck;	// ´ý×öÊý
	bool *chkArray;	// ¼ì²é¾ØÕó
};

struct wNode {
	char word[128];			// Ô­´Ê
	char anno[1792];		// ×¢ÊÍ
	char Userword[128];		// ÓÃ»§Æ´Ð´
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