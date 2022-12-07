#include "Header.h"

int main() {
	system("chcp 1251>nul");
	setlocale(LC_ALL, "Russian");
	HANDLE hRead = CreateThread(NULL, NULL, ConsoleRead, NULL, NULL, NULL);
	char* lasttext = calloc(2048, 1);
	while (TRUE)
	{
		Sleep(300);
		LPWSTR outtext = CBOuput();
		char* text = calloc(2048, 1);
		wcstombs(text, outtext, 2048);

		if (strcmp(lasttext, text)) {
			wcstombs(lasttext, outtext, 2048);
			char newtext[2048] = "";
			if (text != NULL) {
				int size = strlen(text);
				for (size_t i = 0; i < size; i++)
				{
					if (isdigit(*text)) {
						int a = *text - '0';
						strcat(newtext, print_as_digits(a));
					}
					else {
						strncat(newtext, text, 1);
					}
					text++;
				}
				wchar_t* wtext = convertCharArrayToLPCWSTR(newtext);
				LPWSTR ptr = wtext;
				CBInput(ptr);
				wcstombs(lasttext, ptr, 2048);
				printf("Скопировано: %s\n", newtext);
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
	//EmptyClipboard();
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (TRUE)
	{
		gets(text);
		wchar_t* wtext = convertCharArrayToLPCWSTR(text);
		LPWSTR ptr = wtext;
		if (wcslen(ptr) > 0)
		{
			CBInput(ptr);
		}
	}
}

wchar_t* convertCharArrayToLPCWSTR(char* charArray)
{
	wchar_t* wString[512];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

char* print_as_digits(int n) {
	if (n) {
		print_as_digits(n / 10);
		return DIGITS[n % 10];
	}
}