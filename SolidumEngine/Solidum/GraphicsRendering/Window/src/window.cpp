#include "..\include\window.h"

window* window::singletonInstance = nullptr;

window * window::getInstance()
{
	return singletonInstance;
}

window::window(windowConfigBlock *config)
{
	if (singletonInstance == nullptr)
		singletonInstance = this;
	else
		return;

	this->screen_height = config->screen_height;
	this->screen_width = config->screen_width;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = config->hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	wr = { 0, 0, screen_width, screen_height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",
		L"SolidumEngine",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		config->hInstance,
		NULL);

	ShowWindow(hWnd, config->nCmdShow);
}


window::~window()
{
}

void window::pollWin32Events()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			running = false;
	}
}

WPARAM window::destroyWindow()
{
	return WPARAM();
}

void window::update()
{
	pollWin32Events();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}