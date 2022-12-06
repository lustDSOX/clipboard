#include "Header.h"

int main() {
	system("chcp 1251>nul");
	//setlocale(LC_ALL, "Russian");
	//HANDLE hRead = CreateThread(NULL, NULL, ConsoleRead, NULL, NULL, NULL);
	char buffer[512];
	while (TRUE)
	{
		Sleep(100);
		//LPWSTR text = CBOuput();
		char* text = "ads12";
		if (text != NULL) {
			for (size_t i = 0; i < strlen(text); i++)
			{
				if (isdigit(text[i])) {
					insert_substring(text, print_as_digits(text[i]), i);
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

char* print_as_digits(unsigned n) {
	if (n) {
		print_as_digits(n / 10);
		return DIGITS[n % 10];
	}
}
void insert_substring(char* a, char* b, int position)
{
	char* f, * e;
	int length;

	length = strlen(a);

	f = substring(a, 1, position);
	e = substring(a, position+2, length - position+1);

	strcpy(a, "");
	strcat(a, f);
	strcat(a, b);
	strcat(a, e);
}
char* substring(char* string, int position, int length)
{
	char* pointer;
	int c;

	pointer = malloc(length + 1);

	if (pointer == NULL)
		exit(EXIT_FAILURE);

	for (c = 0; c < length; c++)
		*(pointer + c) = *((string + position - 1) + c);

	*(pointer + c) = '\0';

	return pointer;
}