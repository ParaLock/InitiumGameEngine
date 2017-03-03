#pragma once

#include <windows.h>

extern LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct windowConfigBlock {

	int screen_width;
	int screen_height;

	UINT style = CS_HREDRAW | CS_VREDRAW;
	WNDPROC WndProc = WindowProc;
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	HBRUSH hbrBackground = (HBRUSH)COLOR_WINDOW;
	LPCWSTR lpszClassName = L"WindowClass1";

	HINSTANCE hInstance;
	int nCmdShow;
};

class window
{
private:
	WNDCLASSEX wc;
	MSG msg = { 0 };
	RECT wr;

public:
	window(windowConfigBlock *config);

	~window();

	bool running;

	int screen_width;
	int screen_height;

	HWND hWnd;

	void pollWin32Events();
	WPARAM destroyWindow();

	void update();

	static window* singletonInstance;
	static window* getInstance();
};

