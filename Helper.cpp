#include "Helper.h"

LPCWSTR Helper::ConvertToWideChar(const char* str) {
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wchar_t* wideStr = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wideStr, len);
	return wideStr;
}