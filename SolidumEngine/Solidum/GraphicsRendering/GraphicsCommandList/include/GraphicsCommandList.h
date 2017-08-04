#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../ResourceFramework/include/ResourceCreator.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

class GraphicsCommandList
{
private:
	
	ResourceCreator* _resourceCreator;

	std::list<IGraphicsCommand*> _loadedCommands;
public:
	GraphicsCommandList(ResourceCreator* resourceCreator)
		: _resourceCreator(resourceCreator) 
	{
	};

	~GraphicsCommandList();

	void setRenderStateFlags() {};

	void commandLoadedCallback(IResource* loadedCmd);

	template<typename T_CMD>
	void createCommand(typename T_CMD::InitData* params) {

		_resourceCreator->createResourceDeferred<T_CMD>(params, "",
			std::bind(&GraphicsCommandList::commandLoadedCallback, this, std::placeholders::_1)
		);
	}


	void executeCommands();

	void reset();
};

