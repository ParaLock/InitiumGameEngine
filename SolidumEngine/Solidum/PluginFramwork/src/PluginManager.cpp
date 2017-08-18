#include "../include/PluginManager.h"


#include <Strsafe.h>

PluginManager::PluginManager(ResourceCreator& creator, IEngineInstance* sysInstance) :
	_resCreator(creator),
	_sysInstance(sysInstance)
{
}


PluginManager::~PluginManager()
{
}

IPlugin * PluginManager::loadPlugin(std::string pluginFilepath, std::string descFilePath, IEngineInstance* sysInstance)
{
	std::wstring ws;
	ws.assign(pluginFilepath.begin(), pluginFilepath.end());

	HINSTANCE pluginHook = LoadLibrary(ws.c_str());

	if (!pluginHook) {
		std::cout << "Plugin Manager: Could not load plugin" << std::endl;
		std::cout << GetLastError() << std::endl;
		return nullptr;
	}

	plugin_get_instance get_instance = (plugin_get_instance)GetProcAddress(pluginHook, "get_interface_instance");

	if (!get_instance) {
		std::cout << "Plugin Manager: Plugin: Could not find get instance function" << std::endl;
		return nullptr;
	}

	IPlugin* pluginInterface = get_instance();

	switch (pluginInterface->getType()) {
	case PLUGIN_TYPE::COMPONENT_PLUGIN:

		break;
	case PLUGIN_TYPE::RENDER_PASS_PLUGIN:

		RenderPassPluginWrapper* plugin = _resCreator.createResourceImmediate<RenderPassPluginWrapper>(
			&RenderPassPluginWrapper::InitData(descFilePath, &_resCreator),
			"placeholder_name",
			[=](IResource* res) { ResourceUtils::addResourceToGroup(
				res,
				std::string("PluginGroup"), 
				_sysInstance);}
		);

		plugin->setPluginInterface((IRenderPassPlugin*)pluginInterface);

		sysInstance->getGraphicsSubsystem()->registerRenderPass(plugin);

		break;

	//default:
	//	std::cout << "Plugin Manager: Invalid plugin type...." << std::endl;
	//	break;
	}


	return nullptr;
}
