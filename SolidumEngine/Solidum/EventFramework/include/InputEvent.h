#pragma once
#include "IEvent.h"

class InputEvent : public IEvent
{
private:
	std::pair<unsigned long, unsigned long> _mousePos;
	std::list<KEY_MAP> _keysPressed;
public:
	InputEvent();
	~InputEvent();

	void setMousePos(std::pair<unsigned long, unsigned long> mousePos) { _mousePos = mousePos; }
	void setPressedKeys(std::list<KEY_MAP> keysPressed) { _keysPressed = keysPressed; }

	std::pair<unsigned long, unsigned long> getMousePos() { return _mousePos; }
	std::list<KEY_MAP> getPressedKeys() { return _keysPressed; }
};

