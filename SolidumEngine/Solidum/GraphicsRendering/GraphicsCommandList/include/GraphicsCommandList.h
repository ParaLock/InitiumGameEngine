#pragma once
#include "../../../sysInclude.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../GraphicsCommand/include/GraphicsCommandFactory.h"
#include "../../GraphicsCommand/include/GraphicsCommandPool.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

class GraphicsCommandList
{
private:
	struct unloadedCommandData {
		std::shared_ptr<IResourceBuilder> _initData;
		GRAPHICS_COMMAND_TYPE _type;

		unloadedCommandData(std::shared_ptr<IResourceBuilder> initData, GRAPHICS_COMMAND_TYPE type) {
			_initData = initData;
			_type = type;
		}
	};

	std::list<unloadedCommandData> _unloadedCommands;
	std::list<GraphicsCommand*> _loadedCommands;
public:
	GraphicsCommandList();
	~GraphicsCommandList();

	void setRenderStateFlags() {};

	void loadCommands();

	void createCommand(std::shared_ptr<IResourceBuilder> builder, GRAPHICS_COMMAND_TYPE type);

	void executeCommands();
};

