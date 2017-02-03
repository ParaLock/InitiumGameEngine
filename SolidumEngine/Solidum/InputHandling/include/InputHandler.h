#pragma once
#include "../../ResourceFramework/include/IResource.h"
#include "../../ResourceFramework/include/IResourceBuilder.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../EventFramework/include/IEventPublisher.h"

#include "../../EventFramework/include/InputEvent.h"

#include "../../GraphicsRendering/Window/include/windowAccessor.h"


class InputHandler : public IResource, public IEventPublisher
{
public:
	InputHandler();
	~InputHandler();

	void load(IResourceBuilder* builder) { isLoaded = true; }
	void unload() { isLoaded = false; }

	std::pair<unsigned long, unsigned long> getMousePos();
	std::list<KEY_MAP> getPressedKeys();

	void update();
};

