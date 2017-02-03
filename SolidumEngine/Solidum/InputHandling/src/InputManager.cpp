#include "../include/InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

IResource * InputManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	InputHandler* handler = new InputHandler();

	if (loadAsync) {

	}
	else {
		handler->load(builder);
	}

	_activeResources->insert({name, handler});

	return handler;
}
