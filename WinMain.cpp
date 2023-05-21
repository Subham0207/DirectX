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

	try{
		Window wnd(512, 768, "Donkey Box");

		wnd.kbd.EnableAutorepeat();
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			//basically if we don't use WM_CHAR we can remove the Translate message method
			TranslateMessage(&msg); // Translate message could generate other messages; If event is a KEYDOWN then this generaates a WM_CHAR and posts it to the queue;
			DispatchMessageW(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBoxA(nullptr, "something happened", "ALT key is pressed", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (gResult == -1) {
			return -1;
		}
		else {
			return msg.wParam; // msdn docs for WM_QUIT -- wparam and lparam value
		}
	}
	catch (const ChiliException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
	
}