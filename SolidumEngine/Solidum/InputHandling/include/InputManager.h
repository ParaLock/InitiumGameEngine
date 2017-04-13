#pragma once
#include "../../sysInclude.h"

#include "../../ResourceFramework/include/IResourceManager.h"
#include "../../ResourceFramework/include/IResourceBuilder.h"

#include "InputHandler.h"


class InputManager : public IResourceManager
{
public:
	InputManager();
	~InputManager();

	IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

