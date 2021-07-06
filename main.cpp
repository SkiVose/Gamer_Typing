#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <algorithm>
#include "netFetch.h"
#include "gloVar.h"

char* dirPath;
char modePath[128];
// = "D:\\wordhub\\*.csv";
vector<string> files;
bool checkMode = false;
bool showAnno = true;

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

bool getFiles(char* path, vector<string> &vfiles, bool slient) {
	long Handle;
	struct _finddata_t FileInfo;
	vfiles.clear();
	cout << path << endl;
	// system("pause");
	if ((Handle = _findfirst(path, &FileInfo)) == -1L) {
		if (!slient) {
			CC(_WR);
			cout << "[ERROR]";
			CC(_WB_1);
			printf("没有找到该CSV文件或目录不存在...\n");
		}
		return false;
	}
	else
	{
		// printf("%s\n", FileInfo.name);
		vfiles.push_back(FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
			// printf("%s\n", FileInfo.name);
			vfiles.push_back(FileInfo.name);
		_findclose(Handle);
	}
	return true;
}

// 主界面
bool mainPage() {
	char ch;
	while (1) {
		fill(modePath, modePath + 128, 0);

		system("cls");
		CC(_WC);
		cout << "<路径选择>";
		CC(_WB_1);
		cout << " ";

		CC(_GB);
		cout << "[1]_本地目录_";
		CC(_WB_1);
		cout << "  ";

		CC(_GB);
		cout << "[2]_下载目录_";
		CC(_WB_1);
		cout << "  ";

		if (_network)
			CC(_GB);
		else
			CC(_RB);
		cout << "[3]_在线下载_";
		CC(_WB_1);
		cout << endl;

		cout << "输入序号以选择: ";

		ch = _getch();
		if ((int)ch == 49) {
			sprintf(modePath, "%s\\doc\\*.csv", dirPath);
			localPage(modePath);
		}
		else if ((int)ch == 50) {
			sprintf(modePath, "%s\\download\\*.csv", dirPath);
			localPage(modePath);
		}
		else if ((int) ch == 51) {
			if (_network) {
				onlinePage();
			}
			else {
				CC(_WR);
				cout << "连接不可用";
				Sleep(1000);
				CC(_WB_1);
			}
		}
		else {
			CC(_WR);
			cout << "无效输入";
			Sleep(1000);
			CC(_WB_1);
		}
	}
}

// 本地目录选择界面
bool localPage(char *mPath) {
	system("cls");
	if (!getFiles(mPath, files, false)) {
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
			return true;
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

// 在线下载界面
bool onlinePage() {
	if (!_network) return false;
	bool dlcheck = false;		// 下载检查
	vector<string> dlfiles;		// 下载文件路径
	char dlpath[128];			// 下载目录
	char* relpath;				// 程序目录
	if ((dirPath = _getcwd(NULL, 0)) == NULL) {
		cout << "_getcwd Error!";
		system("pause");
		return false;
	}
	sprintf(dlpath, "%s\\download\\*.csv", dirPath);
	// free(dirPath);

	if (!getFiles(dlpath, dlfiles, true)) {
		/*CC(_WR);
		cout << "[ERROR]";
		CC(_WB_1);
		cout << "虽然不影响正常使用,但我还是要报错..." << endl;
		system("pause");
		return false;*/
	}
	else dlcheck = true;

	CC(_WC);
	cout << "[INFO]";
	CC(_WB_1);
	printf(" 正在请求远程文件列表");

	stringstream ss;
	string str;
	int total = 0, times = 0, pos = -1;
	_NetSendReq((char*)"0", _REQ_GL);		// 请求文件列表

	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(1000);
	}	// 等待3s

	if (_swapFile(files) == false) {
		_netstate == _REQ_NONE;
		CC(_WR);
		cout << "[ERROR]";
		CC(_WB_1);
		printf(" 获取线上文件列表失败...");
		system("pause");
		return false;
	}
	/*for (int i = 0; i < files.size(); i++) {
		cout << files[i] << endl;
	}cout << endl;*/
	
	// system("pause");

	char ch;
	int tmpIdx = 0;
	int page = 0, tpage = files.size() / 3;
	if (files.size() % 3 != 0) tpage++;
	while (1) {
		system("cls");
		printf("请选择要下载的练习文档[%d/%d]:", page + 1, tpage);

		for (int i = page * 3; i < (page + 1) * 3; i++) {
			if (i >= files.size()) break;
			if (dlcheck) {
				vector<string>::iterator it = find(dlfiles.begin(), dlfiles.end(), files[i]);
				if (it != dlfiles.end()) {
					CC(_CB);
					printf("[%d]%s    ", i + 1, files[i].c_str());
				}
				else {
					CC(_GB);
					printf("[%d]%s    ", i + 1, files[i].c_str());
				}
				CC(_WB_1);
			}
			else {
				CC(_GB);
				printf("[%d]%s    ", i + 1, files[i].c_str());
				CC(_WB_1);
			}
			
		}
		printf("\n");

		cout << " # ";
		CC(_WC);
		printf("[-]上一页, [=]下一页");
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
			if (!_network) {
				cout << endl;
				CC(_WR);
				cout << "[ERROR]";
				CC(_WB_1);
				printf(" 与服务器连接已断开...");
				system("pause");
				return false;
			}

			if (tmpIdx > 0 && tmpIdx <= files.size()) {
				// 下载模块
				_NetSendReq((char*)files[tmpIdx - 1].c_str(), _REQ_DL);		// 请求文件列表
				// system("cls");
				Sleep(3000);
				if (_netFinish == _REQ_DL) {	// 正常结束
					_netFinish = _REQ_NONE;
					CC(_WC);
					printf("DONE!");
					CC(_WB_1);
					system("pause");
				}
				else if(_netstate == _REQ_DL){	// 网络问题
					_netstate = _REQ_NONE;
					CC(_WR);
					printf("DOWNLOAD FAID!");
					CC(_WB_1);
					system("pause");
				}
				else {
					if (_retval == -1) {
						cout << endl;
						CC(_WR);
						cout << "[ERROR]";
						CC(_WB_1);
						printf(" 该文件已存在...");
						system("pause");
					}
					else if (_retval == -2) {
						cout << endl;
						CC(_WR);
						cout << "[ERROR]";
						CC(_WB_1);
						cout << "文件无法打开!" << endl;
						system("pause");
					}
					else {
						cout << endl;
						CC(_WR);
						cout << "[ERROR]";
						CC(_WB_1);
						printf("某些原因导致不可用! [%d]", _retval);
						system("pause");
					}
				}
				tmpIdx = 0;
			}
			else {
				cout << " ";
				CC(_WR);
				cout << "序号不存在";
				CC(_WB_1);
				Sleep(1000);
			}

			if (!getFiles(dlpath, dlfiles, true))
				dlcheck = false;
			else dlcheck = true;
		}
		else if ((int)ch == 27) {
			// ESC
			return true;
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

	return true;
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

void main() {
	system("mode con:cols=100 lines=3");
	// ReadCsvdata(path);
	// PrintWords();
	// TypingPage();

	if ((dirPath = _getcwd(NULL, 0)) == NULL) {
		CC(_WR);
		perror("_getcwd Error!");
		CC(_WB_1);
		system("pause");
		return;
	}

	if(!DLL_init()) {
		CC(_WR);
		perror("winsock malloc failed!");
		CC(_WB_1);
		system("pause");
		return;
	}

	HANDLE NetThread = CreateThread(NULL, 0, _NetInit, 0, 0, NULL);
	if (NetThread == NULL) {
		cout << "[Thread Error]: TimerThread create failed." << endl;
	}
	else {
		CloseHandle(NetThread);
	}
	Sleep(1000);

	while (1) {
		mainPage();
	}
}