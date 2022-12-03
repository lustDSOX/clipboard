#include "Header.h"

main() {
	setlocale(LC_ALL, "Russian");
	while (TRUE)
	{
		Sleep(100);
		LPWSTR text = CBOuput();
		if (text != NULL) {
			wprintf(L"%s\n", text);
		}
	}
}

LPWSTR CBOuput() {
	LPWSTR text = NULL;
	OpenClipboard(NULL);
	HANDLE CBtext = GetClipboardData(CF_UNICODETEXT);
	text = (LPWSTR)GlobalLock(CBtext);
	GlobalUnlock(CBtext);
	EmptyClipboard();
	CloseClipboard();
	return text;
}