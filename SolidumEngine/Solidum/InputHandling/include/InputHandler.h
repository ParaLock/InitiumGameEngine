#pragma once
#include "../../ResourceFramework/include/IResource.h"
#include "../../ResourceFramework/include/IResourceBuilder.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../EventFramework/include/Event.h"

#include "../../GraphicsRendering/Window/include/window.h"


struct InputEvtData : public EventData {

	std::pair<unsigned long, unsigned long> _mousePos;
	std::list<KEY_MAP> _keysPressed;

	void setMousePos(std::pair<unsigned long, unsigned long> mousePos) { _mousePos = mousePos; }
	void setPressedKeys(std::list<KEY_MAP> keysPressed) { _keysPressed = keysPressed; }

	std::pair<unsigned long, unsigned long> getMousePos() { return _mousePos; }
	std::list<KEY_MAP> getPressedKeys() { return _keysPressed; }
};

class InputHandler : public IResource, public IEventListener
{
private:
public:
	InputHandler();
	~InputHandler();

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; }
	void unload() { isLoaded = false; }

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::pair<unsigned long, unsigned long> getMousePos();
	std::list<KEY_MAP> getPressedKeys();

	void onEvent(EVENT_PTR evt);

	void update();
};

