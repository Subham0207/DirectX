#pragma once
#include <Windows.h>

class Helper
{
public:
	static LPCWSTR ConvertToWideChar(const char* str);
};