#pragma once
#include "../../sysInclude.h"

#include "../../../SolidumAPI/core_interfaces/IPlugin.h"

#include "../../../SolidumAPI/core_interfaces/IRenderPassPlugin.h"
#include "../../../SolidumAPI/core_interfaces/IComponentPlugin.h"

#include "../../GraphicsRendering/RenderPass/include/RenderPassPluginWrapper.h"

#include "../../ResourceFramework/include/ResourceCreator.h"

class PluginManager
{
private:
	ResourceCreator& _resCreator;
	IEngineInstance* _sysInstance;

	typedef IPlugin*(*plugin_get_instance)();
public:
	PluginManager(ResourceCreator& creator, IEngineInstance* sysInstance);
	~PluginManager();

	IPlugin* loadPlugin(std::string pluginFilepath, std::string descFilePath, IEngineInstance* sysInstance);
};

