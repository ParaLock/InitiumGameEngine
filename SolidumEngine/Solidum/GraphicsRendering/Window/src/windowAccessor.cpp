#include "../include/windowAccessor.h"

HWND windowAccessor::hWnd = NULL;

int windowAccessor::screen_height = NULL;
int windowAccessor::screen_width = NULL;

void windowAccessor::initAccessor(window * windowIN)
{
	hWnd = windowIN->hWnd;
	screen_height = windowIN->screen_height;
	screen_width = windowIN->screen_width;
}
