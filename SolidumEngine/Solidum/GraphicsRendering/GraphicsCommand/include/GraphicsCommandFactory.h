#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsCommand/include/GraphicsCommand.h"
#include "../../../ResourceFramework/include/ResourceFactory.h"

#include "../../ShaderCommands/include/ShaderCommand.h"
#include "../../PipelineCommands/include/PipelineCommand.h"

class GraphicsCommandFactory : public ResourceFactory<GraphicsCommand, GRAPHICS_COMMAND_TYPE>
{
public:
	GraphicsCommandFactory();
	~GraphicsCommandFactory();

	GraphicsCommand* createObject(GRAPHICS_COMMAND_TYPE type);
};

