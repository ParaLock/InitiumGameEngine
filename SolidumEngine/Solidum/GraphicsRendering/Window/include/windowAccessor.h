#pragma once

#include "../include/window.h"

class windowAccessor
{
public:
	static void initAccessor(window *windowIN);

	static HWND hWnd;

	static int screen_height;
	static int screen_width;
};

