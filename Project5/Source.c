#include "Header.h"

int main() {
	system("chcp 1251>nul");
	//setlocale(LC_ALL, "Russian");
	HANDLE file = CreateFile(L"text.docx", GENERIC_WRITE || FILE_SHARE_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hRead = CreateThread(NULL, NULL, ConsoleRead, NULL, NULL, NULL);
	char buffer[512];
	while (TRUE)
	{
		Sleep(100);
		LPWSTR text = CBOuput();
		if (text != NULL) {
			if (lstrlen(text) == 1) {
				if (text[0] == '1') {
					text = L"1-один";
				}
				else if (text[0] == '2') {
					text = L"2-два";
				}
				else if (text[0] == '3') {
					text = L"3-три";
				}
				else if (text[0] == '4') {
					text = L"4-четыре";
				}
				else if (text[0] == '5') {
					text = L"5-пять";
				}
				else if (text[0] == '6') {
					text = L"6-шесть";
				}
				else if (text[0] == '7') {
					text = L"7-семь";
				}
				else if (text[0] == '8') {
					text = L"8-восемь";
				}
				else if (text[0] == '9') {
					text = L"9-девять";
				}
				else if (text[0] == '0') {
					text = L"0-ноль";
				}
				CBInput(text);
			}
			else {
				if (file) {
					wcstombs(&buffer, text, 512);
					WriteFile(file, buffer, strlen(buffer), NULL, NULL);
					OpenClipboard(NULL);
					EmptyClipboard();
					CloseClipboard();
				}
			}
		}
	}
}

LPWSTR CBOuput() {
	LPWSTR text = NULL;
	OpenClipboard(NULL);
	HANDLE CBtext = GetClipboardData(CF_UNICODETEXT);
	text = (LPWSTR)GlobalLock(CBtext);
	GlobalUnlock(CBtext);
	CloseClipboard();
	return text;
}

void CBInput(LPWSTR text) {
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE, (wcslen(text) + 1) * sizeof(LPWSTR));
	memcpy(GlobalLock(hMem), text, (wcslen(text) + 1) * sizeof(LPWSTR));
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
}

void ConsoleRead() {
	char text[512];
	wchar_t  wtext[512];
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (TRUE)
	{
		scanf("%s", text);
		mbstowcs(wtext, text, strlen(text) + 1);//Plus null
		LPWSTR ptr = wtext;
		if (wcslen(ptr) > 0)
		{
			CBInput(ptr);
		}
	}
}