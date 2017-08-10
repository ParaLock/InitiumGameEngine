#pragma once
#include "../../ResourceFramework/include/Resource.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../EventFramework/include/Event.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../ResourceFramework/include/GenericFactory.h"

#include "../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

struct InputEvtData : public EventData {

	std::pair<unsigned long, unsigned long> _mousePos;
	std::list<KEY_MAP> _keysPressed;

	void setMousePos(std::pair<unsigned long, unsigned long> mousePos) { _mousePos = mousePos; }
	void setPressedKeys(std::list<KEY_MAP> keysPressed) { _keysPressed = keysPressed; }

	std::pair<unsigned long, unsigned long> getMousePos() { return _mousePos; }
	std::list<KEY_MAP> getPressedKeys() { return _keysPressed; }
};

class ResourcePool;

class InputHandler : public IEventListener, public Resource<InputHandler, GenericFactory, ResourcePool>
{
private:
public:
	InputHandler();
	~InputHandler();

	struct InitData : public ResourceInitParams {

		

		InitData() {}
	};

	void load() {}
	void unload() {}

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::pair<unsigned long, unsigned long> getMousePos();
	std::list<KEY_MAP> getPressedKeys();

	void onEvent(EVENT_PTR evt);

	void update();

protected:
};

