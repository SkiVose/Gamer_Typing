#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <io.h>
#include <Windows.h>
#include <direct.h>
#include <time.h>

char modePath[128];
// = "D:\\wordhub\\*.csv";
vector<string> files;
bool checkMode = false;
bool showAnno = true;

time_t endts = 1623921300;

// 读取csv文件
bool ReadCsvdata(char* path) {
	// cout << path << endl;
	// system("pause");
	ifstream inFile(path, ios::in);
	int idxCounter = 0;
	string lineStr;
	getline(inFile, lineStr);
	while (getline(inFile, lineStr)) {
		idxCounter = 0;
		// cout << lineStr << endl;
		stringstream ss(lineStr);
		string str;

		wNode* node = (wNode*)malloc(sizeof(wNode));
		fill(node->Userword, node->Userword + 128, 0);
		while (getline(ss, str, ',')) {
			// cout << str << endl;
			if (++idxCounter == 1) strcpy(node->word, str.c_str());
			else strcpy(node->anno, str.c_str());
		}
		strArray.push_back(node);
		
	}
	inFile.close();
	return true;
}

// 打印
bool PrintWords() {
	for (int i = 0; i < strArray.size(); i++) {
		printf("[%02d] %s %s\n", i, strArray[i]->word, strArray[i]->anno);
	}
	return true;
}

bool getFiles(char* path) {
	long Handle;
	struct _finddata_t FileInfo;
	files.clear();
	// cout << path << endl;
	if ((Handle = _findfirst(path, &FileInfo)) == -1L) {
		CC(_WR);
		cout << "[ERROR]";
		CC(_WB_1);
		printf("没有找到该CSV文件或目录不存在...\n");
		return false;
	}
	else
	{
		// printf("%s\n", FileInfo.name);
		files.push_back(FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
			// printf("%s\n", FileInfo.name);
			files.push_back(FileInfo.name);
		_findclose(Handle);
	}
	return true;
}

// choose界面
bool ChoosePage(char *mPath) {
	if (!getFiles(mPath)) {
		// system("pause");
		cout << "Press anykey to reload... ESC to exit.";
		char ch = _getch();
		if ((int)ch == 27) {
			// ESC
			return true;
		}
		else {

			system("cls");
			return false;
		}
	}
	char ch;
	int tmpIdx = 0;
	int page = 0, tpage = files.size() / 3;
	if (files.size() % 3 != 0) tpage++;

	while (1) {
		system("cls");
		printf("请选择你的练习文档[%d/%d]:", page+1, tpage);

		CC(_GB);
		for (int i = page * 3; i < (page + 1) * 3; i++) {
			if (i >= files.size()) break;
			printf("[%d]%s    ", i + 1, files[i].c_str());
		}
		CC(_WB_1);
		printf("\n");

		cout << " # ";
		CC(_WC);
		printf("[-]上一页, [=]下一页, [\\]切换检查模式, [TAB]单词纠正补全");
		CC(_WB_1);
		cout << " # ";
		printf("输入文档前序号回车完成选择):");

		if (tmpIdx != 0) {
			CC(_YB);
			printf("%d", tmpIdx);
			CC(_WB_1);
		}
		ch = _getch();
		if (isdigit(ch)) {
			tmpIdx = tmpIdx * 10 + (int)(ch - '0');
		}
		else if ((int)ch == 8) {
			// DEL
			tmpIdx /= 10;
		}
		else if ((int)ch == 13) {
			// ENTER
			if (tmpIdx > 0 && tmpIdx <= files.size()) {
				string dictPath = mPath;
				string filepath = dictPath.substr(0, dictPath.find("*"));
				filepath.append(files[tmpIdx - 1]);
				ReadCsvdata((char*)filepath.c_str());
				TypingPage();
				tmpIdx = 0;
			}
			else {
				cout << " ";
				CC(_WR);
				cout << "序号不存在";
				CC(_WB_1);
				Sleep(1000);
			}
		}
		else if ((int)ch == 27) {
			// ESC
			// return true;
		}
		else if ((int)ch == 45) {
			// -
			page = (page + tpage - 1) % tpage;
		}
		else if ((int)ch == 61) {
			// =
			page = (page + 1) % tpage;
		}
	}
}

// type界面
void TypingPage() {
	CountBoard* cb = (CountBoard*)malloc(sizeof(CountBoard));
	cb->cur = cb->checked = cb->right = cb->wrong = 0;
	cb->total = cb->uncheck = strArray.size();
	cb->chkArray = (bool*)malloc(sizeof(bool) * cb->total);
	fill(cb->chkArray, cb->chkArray + cb->total, 0);

	string typingStr = "";
	while (1) {
		PrintHeader(typingStr, cb);
		unsigned char c = _getch();
		// cout << (int)c << endl;
		// Sleep(1000);
		if (isalpha(c)) {
			// 字母
			if (typingStr.length() >= strlen(strArray[cb->cur]->word))
				continue;
			if (isupper(c))
				c = tolower(c);
			typingStr.push_back(c);
		}
		else if ((int)c == 8) {
			// DEL
			if (typingStr.empty()) continue;
			typingStr.pop_back();
		}
		else if ((int)c == 9) {
			// TAB
			int i = 0;
			for (i = 0; i < typingStr.length(); i++) {
				if (strArray[cb->cur]->word[i] != typingStr[i])
					break;
			}

			if (i < typingStr.length()) {
				for (int i = 0; i < typingStr.length(); i++) {
					if (i == 0) cout << " #";
					if (strArray[cb->cur]->word[i] == typingStr[i]) {
						CC(_GB);
						cout << typingStr[i];
					}
					else {
						CC(_RB);
						cout << typingStr[i];
					}
				}
				CC(_WB_1);
			}

			CC(_WC);
			for (i = typingStr.length(); i < strlen(strArray[cb->cur]->word); i++) {
				cout << strArray[cb->cur]->word[i];
			}
			// cout << strArray[cb->cur]->word;
			CC(_WB_1);
			Sleep(250);
		}
		else if ((int)c == 13) {
			// ENTER
			strcpy(strArray[cb->cur]->Userword, typingStr.c_str());
			
			cout << " ";
			if (cb->chkArray[cb->cur]) {
				// 已经检查过的的
				if (CheckSpell(typingStr, cb)) {	// 拼写检查
					CC(_WG);
					cout << "Right!";
					CC(_WB_1);
					Sleep(1000);
				}
				else {
					CC(_WR);
					cout << "Wrong!";
					CC(_WB_1);
					Sleep(1000);
				}
			}
			else {
				// 没有检查过的
				if (CheckSpell(typingStr, cb)) {	// 拼写检查
					CC(_WG);
					cout << "Right!";
					CC(_WB_1);
					Sleep(1000);

					cb->right++;
				}
				else {
					CC(_WR);
					cout << "Wrong!";
					CC(_WB_1);
					Sleep(1000);

					cb->wrong++;
				}
				cb->checked++;
				cb->uncheck--;
				cb->chkArray[cb->cur] = true;
			}
			typingStr.clear();
			if (cb->cur + 1 >= cb->total)
				FinishType(cb);
			else cb->cur++;
		}
		else if ((int)c == 27) {
			// ESC
			break;
		}
		else if ((int)c == 45) {
			// - 上一个
			if (cb->cur - 1 < 0) {
				// 最先的单词
				continue;
			}
			else {
				typingStr.clear();
				cb->cur--;
				typingStr = strArray[cb->cur]->Userword;
			}
		}else if ((int)c == 27) {
			// ESC
			break;
		}
		else if ((int)c == 61) {
			// = 下一个
			if (cb->cur + 1 >= cb->total) {
				// 读完了所有单词
				FinishType(cb);
			}
			else {
				++cb->cur;
				if (cb->chkArray[cb->cur]) {
					// 已经check过的
					typingStr = strArray[cb->cur]->Userword;
				}
				else {
					// 没有check过
					typingStr.clear();
				}

				
			}
		}
		else if ((int)c == 92) {
			cout << " ";
			if (!checkMode) {
				CC(_WC);
				cout << "逐字检查已开启";
				checkMode = true;
			}
			else {
				CC(_WP);
				cout << "逐字检查已关闭";
				checkMode = false;
			}
			CC(_WB_1);
			Sleep(1000);
		}
		else if ((int)c == 96) {
		// space 显示注释开关
		cout << " ";
		if (showAnno) {
			showAnno = false;
			CC(_WC);
			printf("隐藏注释");
		}
		else {
			showAnno = true;
			CC(_WP);
			printf("显示注释");
		}
		CC(_WB_1);
		Sleep(1000);
		continue;
		}
		else {

		}
	}

	// 结束时释放空间
	free(cb->chkArray);
	free(cb);

	for (int i = 0; i < strArray.size(); i++) {
		free(strArray[i]);
	}
	strArray.clear();
}

void PrintHeader(string str, CountBoard *cb) {
	system("cls");

	cout << "# "; CC(_WY);
	cout << "Current"; CC(_WB_1);
	cout << "/"; CC(_WB_2);
	cout << "Checked"; CC(_WB_1);
	cout << "/"; CC(_WP);
	cout << "Total"; CC(_WB_1);
	cout << ":"; CC(_YB);
	cout << cb->cur + 1; CC(_WB_1);
	cout << "/"; CC(_BB);
	cout << cb->checked; CC(_WB_1);
	cout << "/"; CC(_PB);
	cout << cb->total << '\t'; CC(_WG);
	cout << "Right"; CC(_WB_1);
	cout << "/"; CC(_WR);
	cout << "Wrong"; CC(_WB_1);
	cout << ":"; CC(_GB);
	cout << cb->right; CC(_WB_1);
	cout << "/"; CC(_RB);
	cout << cb->wrong; CC(_WB_1);
	cout << '\n';


	// printf("- Current/Checked/Total:%d/%d/%d\tRight/Wrong:%d/%d -\n",
	// 	cb->cur+1, cb->checked, cb->total, cb->right, cb->wrong);
	if(showAnno)
		printf("%s:", strArray[cb->cur]->anno);
	if (checkMode) {
		int minLen = strlen(strArray[cb->cur]->word) < str.length() ?
			strlen(strArray[cb->cur]->word) : str.length();
		for (int i = 0; i < minLen; i++) {
			if (strArray[cb->cur]->word[i] == str[i]) {
				CC(_GB);
				cout << str[i];
			}
			else {
				CC(_RB);
				cout << str[i];
			}
		}
		CC(_WB_1);
	}
	else {
		cout << str;
	}
}

void FinishType(CountBoard* cb) {
	system("cls");
	float rate = cb->right * 100.0 / cb->total;

	cout << " * ";
	CC(_WC);
	cout << "congratulations you have finish this practise.";
	CC(_WB_1);
	cout << " * \n # ";

	CC(_WG);
	printf("Your Accuracy is ");

	if (rate < 60) {
		CC(_PB);
		printf("%.2f%%", rate);
		CC(_WB_1);
		cout << ", Better luck next time. # ";
	}
	else if (rate < 80) {
		CC(_YB);
		printf("%.2f%%", rate);
		CC(_WB_1);
		cout << ", Good job! # ";
	}
	else {
		CC(_GB);
		printf("%.2f%%", rate);
		CC(_WB_1);
		cout << ", Perfect! # ";
	}

	system("pause");
}

bool CheckSpell(string str, CountBoard* cb) {
	if (strcmp(str.c_str(), strArray[cb->cur]->word) == 0)
		return true;
	else return false;
}

void CC(char cs) {
	if (cs == _WB_1)		// 黑底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE);
	else if (cs == _WB_2)	// 蓝底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_BLUE);
	else if (cs == _WY)		// 黄底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	else if (cs == _WG)		// 绿底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN);
	else if (cs == _WC)		// 青底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE);
	else if (cs == _WR)		// 红底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED);
	else if (cs == _WP)		// 粉底白字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
			| FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE);


	else if (cs == _BB)	// 黑底蓝字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (cs == _YB)		// 黑底黄字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (cs == _GB)		// 黑底绿字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (cs == _CB)		// 黑底青字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (cs == _RB)		// 黑底红字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (cs == _PB)		// 黑底粉字
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);

}

void main() {
	time_t checkTime = time(NULL);

	system("mode con:cols=100 lines=2");

	if (checkTime > endts) {
		CC(_WR);
		cout << "[TIMEOUT]";
		CC(_WB_1);
		cout << "无效时间...任意键退出...";
		
		char ch = _getch();
		if ((int)ch != 9)
			return;
		system("cls");
	}
	// ReadCsvdata(path);
	// PrintWords();
	// TypingPage();
	char* dirPath;
	if ((dirPath = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd Error!");
	else {
		// cout << dirPath << endl;
		sprintf(modePath, "%s\\doc\\*.csv", dirPath);
		free(dirPath);
		// cout << modePath << endl;
	}

	while (1) {
		if (ChoosePage(modePath))
			break;
	}
}