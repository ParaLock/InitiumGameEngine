#include "../include/InputHandler.h"



InputHandler::InputHandler()
{
	EventFrameworkCore::getInstance()->getGlobalEventHub("CameraEventHub")->subscribeListener(this);
}


InputHandler::~InputHandler()
{
}

std::pair<unsigned long, unsigned long> InputHandler::getMousePos()
{
	POINT mousePos;
	GetCursorPos(&mousePos);

	ScreenToClient(window::getInstance()->hWnd, &mousePos);

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

	if (GetAsyncKeyState('I')) {
		pressedKeyList.push_back(KEY_MAP::I);
	}
	if (GetAsyncKeyState('L')) {
		pressedKeyList.push_back(KEY_MAP::L);
	}
	if (GetAsyncKeyState('K')) {
		pressedKeyList.push_back(KEY_MAP::K);
	}
	if (GetAsyncKeyState('J')) {
		pressedKeyList.push_back(KEY_MAP::J);
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

void InputHandler::onEvent(EVENT_PTR evt)
{
}

void InputHandler::update()
{
	InputEvtData _hotEventData;

	EVENT_PTR inputEventPtr = std::make_shared<Event>();

	inputEventPtr.get()->setType(EVENT_TYPE::INPUT_EVENT);

	std::list<KEY_MAP> keys = getPressedKeys();

	if (keys.size() > 0) {
		_hotEventData.setPressedKeys(keys);
	}
	
	std::pair<unsigned long, unsigned long> mousePos = getMousePos();

	_hotEventData.setMousePos(mousePos);

	inputEventPtr.get()->setData(std::make_shared<InputEvtData>(_hotEventData));

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("InputEventHub")->publishEvent(inputEventPtr);
}
