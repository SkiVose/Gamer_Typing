#pragma once
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
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


void CC(char cs) {
	if (cs == _WB_1)		// ºÚµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE);
	else if (cs == _WB_2)	// À¶µ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_BLUE);
	else if (cs == _WY)		// »Æµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	else if (cs == _WG)		// ÂÌµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN);
	else if (cs == _WC)		// Çàµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE);
	else if (cs == _WR)		// ºìµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED);
	else if (cs == _WP)		// ·Ûµ×°××Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE);


	else if (cs == _BB)	// ºÚµ×À¶×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (cs == _YB)		// ºÚµ×»Æ×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (cs == _GB)		// ºÚµ×ÂÌ×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (cs == _CB)		// ºÚµ×Çà×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (cs == _RB)		// ºÚµ×ºì×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (cs == _PB)		// ºÚµ×·Û×Ö
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);

}