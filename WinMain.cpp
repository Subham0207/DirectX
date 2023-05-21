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

	wnd.kbd.EnableAutorepeat();
	MSG msg;
	BOOL gResult;
	static int i = 0;
	while (( gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		//basically if we don't use WM_CHAR we can remove the Translate message method
		TranslateMessage(&msg); // Translate message could generate other messages; If event is a KEYDOWN then this generaates a WM_CHAR and posts it to the queue;
		DispatchMessageW(&msg);
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			switch(e.GetType())
			{
			case Mouse::Event::Type::Leave:
				wnd.SetTitle("Gone!");
				break;
			case Mouse::Event::Type::Move:
			{
				std::ostringstream oss;
				oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
				wnd.SetTitle(oss.str());
			}
			break;
			case Mouse::Event::Type::WheelUp:
				i++;
				{
					std::ostringstream oss;
					oss << "Up: " << i;
					wnd.SetTitle(oss.str());
				}
				break;
			case Mouse::Event::Type::WheelDown:
				i--;
				{
					std::ostringstream oss;
					oss << "Down: " << i;
					wnd.SetTitle(oss.str());
				}
				break;
			}
		}
	}



	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam; // msdn docs for WM_QUIT -- wparam and lparam value
	}
}