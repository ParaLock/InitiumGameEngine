#pragma once
#include "../../ResourceFramework/include/IResource.h"
#include "../../ResourceFramework/include/IResourceBuilder.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../EventFramework/include/InputEvent.h"

#include "../../GraphicsRendering/Window/include/window.h"


class InputHandler : public IResource, public IEventListener
{
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

