#include<iostream>
#include "WindowsMessageMap.h"
#include <sstream>
#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpcmdline,
	int nCmdShow)
{

	Window wnd(512, 768, "Donkey Box");

	MSG msg;
	BOOL gResult;
	while (( gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		//basically if we don't use WM_CHAR we can remove the Translate message method
		TranslateMessage(&msg); // Translate message could generate other messages; If event is a KEYDOWN then this generaates a WM_CHAR and posts it to the queue;
		DispatchMessageW(&msg);
	}



	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam; // msdn docs for WM_QUIT -- wparam and lparam value
	}
}