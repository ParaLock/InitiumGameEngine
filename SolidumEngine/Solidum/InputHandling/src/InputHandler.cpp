#include "../include/InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

std::pair<unsigned long, unsigned long> InputHandler::getMousePos()
{
	POINT mousePos;
	GetCursorPos(&mousePos);

	ScreenToClient(windowAccessor::hWnd, &mousePos);

	return std::make_pair(mousePos.x, mousePos.y);
}

std::list<KEY_MAP> InputHandler::getPressedKeys()
{
	std::list<KEY_MAP> pressedKeyList;

	if (GetAsyncKeyState('W')) {
		pressedKeyList.push_back(KEY_MAP::W);
	}
	if (GetAsyncKeyState('S')) {
		pressedKeyList.push_back(KEY_MAP::S);
	}
	if (GetAsyncKeyState('A')) {
		pressedKeyList.push_back(KEY_MAP::A);
	}
	if (GetAsyncKeyState('D')) {
		pressedKeyList.push_back(KEY_MAP::D);
	}

	if (GetAsyncKeyState(VK_UP)) {
		pressedKeyList.push_back(KEY_MAP::UP);
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		pressedKeyList.push_back(KEY_MAP::DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		pressedKeyList.push_back(KEY_MAP::LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		pressedKeyList.push_back(KEY_MAP::RIGHT);
	}

	return pressedKeyList;
}

void InputHandler::update()
{
	InputEvent* inputEvent = new InputEvent();

	std::list<KEY_MAP> keys = getPressedKeys();

	if (keys.size() > 0) {
		inputEvent->setPressedKeys(keys);
	}
	
	std::pair<unsigned long, unsigned long> mousePos = getMousePos();

	inputEvent->setMousePos(mousePos);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("InputEventHub")->publishEvent(inputEvent);
}
