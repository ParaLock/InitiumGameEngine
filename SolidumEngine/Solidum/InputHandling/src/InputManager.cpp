#include "../include/InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

IResource * InputManager::createResource(IResourceBuilder * builder, std::string name)
{
	InputHandler* handler = new InputHandler();

	_activeResources->insert({name, handler});

	return handler;
}
