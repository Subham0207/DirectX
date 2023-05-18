#include<iostream>
#include "WindowsMessageMap.h"
#include <sstream>

// LResult may be on the type of message that we are handling
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// you could note the format of a window message to understand it correctly
	// NC - means non client -- everything except the client region ( where we want to actually draw)
	//WM_KEYDOWN -> lp,wp - which key is being pressed
	//WM_KEYUP
	//WM_CHAR
	static WindowsMessageMap mm;
	OutputDebugStringA(mm(msg, lParam, wParam).c_str());

	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(69); //Post this message to the message queue; Exit the application with exit code
		break;
	case WM_KEYDOWN: // shift + D or D will all results in D. No notion of capital letters
		if (wParam == 'F')
		{
			SetWindowTextA(hWnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowTextA(hWnd, "Battlefield");
		}
		break;
	case WM_CHAR: // useful for textinput; And since F1 key doesnot have a representation in text it doesnot have a WM_CHAR; Has notion of capital letters
		{
			static std::string title;
			title.push_back((char)wParam);
			SetWindowTextA(hWnd, title.c_str());
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << "(" << pt.x << "," << pt.y << ")";
			SetWindowTextA(hWnd, oss.str().c_str());
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// CALLBACK - is calling convention - STDCALL -- Any function that you create that the windowsAPI has to call (A callback)
// Lot of windows function have normal version and a Ex for Extended version
// Pattern - configuration struture; Pass a pointer to that structure into a function
int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpcmdline,
	int nCmdShow)
{
	auto pClassName = L"hw3First";

	//Register Window Class 
	// .........Args........
	// size: size of the struture
	// lnfnWndProc: Long pointer to function Window Proc - Pointer the function that is going to handle all the messages for this window
	// HBRUSH: null to tell windows don't draw on the client space; We will use DirectX to do that
	// lpszClassName: register a windows and then use this classname to create instance of the windows with this class type
	// hIconSm: to add icon
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;// DefWindowProc: default list of procedures like closing, moving the window, so on
	wc.cbClsExtra = 0; // extra bytes to create
	wc.cbWndExtra = 0; // extra bytes to create
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	//create window
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		L"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInst, nullptr);

	//Show window
	ShowWindow(hWnd, SW_SHOW);

	//MessageQueue;GetMessageFromQueue;TranslateMSG;DispatchMessage,WindowHasPointerToWindowProcedure( like handle draw message);DefaultWndProcedure;

	//GetMessage:
		//MessageStructure
			// lParam -- depends on the message -- contains data regarding a message
			// wParam -- depends on the message -- contains data regarding a message
		//hWnd: null means get all the messages regardless of the window they come from
		//msgfiltermin: min number of msg to pull; 0 - to get all the messages
		//msgfiltermax: max number of msg to pull; 0 - to get all the messages

		//ReturnValue:
			// Quit msg - 0
			// other msg -- non zero
			// error - -1

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