#pragma once
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
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


void CC(char cs) {
	if (cs == _WB_1)		// �ڵװ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE);
	else if (cs == _WB_2)	// ���װ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_BLUE);
	else if (cs == _WY)		// �Ƶװ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	else if (cs == _WG)		// �̵װ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN);
	else if (cs == _WC)		// ��װ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE);
	else if (cs == _WR)		// ��װ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED);
	else if (cs == _WP)		// �۵װ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE);


	else if (cs == _BB)	// �ڵ�����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (cs == _YB)		// �ڵ׻���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (cs == _GB)		// �ڵ�����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (cs == _CB)		// �ڵ�����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (cs == _RB)		// �ڵ׺���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (cs == _PB)		// �ڵ׷���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);

}