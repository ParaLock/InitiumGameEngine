#pragma once

#include "../../../ResourceFramework/include/Resource.h"
#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"
#include "../../GraphicsCommandList/include/GraphicsCommandList.h"
#include "../../RenderDataProtocal/include/RenderDataGroup.h"
#include "../../../sysInclude.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Shaders/include/ShaderParser.h"
#include "../../Shaders/include/Shader.h"

#include "../../../../SolidumAPI/core_interfaces/IShader.h"

#include "RenderPassDescriptorParser.h"

#include "../../../../SolidumAPI/core_interfaces/IGraphicsCommandBlock.h"
#include "../../../../SolidumAPI/core_interfaces/IRenderPassPlugin.h"
#include "../../../../SolidumAPI/core_interfaces/IRenderFlowGraphIOInterface.h"
#include "../../../../SolidumAPI/core_objects/include/SlabCache.h"

#include "../../../../SolidumAPI/core_interfaces/IRenderPassPluginWrapper.h"

class RenderPassPluginWrapper : public Resource<RenderPassPluginWrapper, GenericFactory, ResourcePool>, public IRenderPassPluginWrapper
{
private:

	IRenderPassPlugin* _pluginInterface;

	SlabCache _cache;

	std::string _name;

	std::map<std::string, IShader*> _shaders;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	RenderFlowGraphIOInterface* _ioInterface;

	GPUPipeline _pso;

public:
	RenderPassPluginWrapper();
	~RenderPassPluginWrapper();

	struct InitData : public ResourceInitParams {

		InitData() {}

		ResourceCreator* _resourceCreator;

		std::string _filename;

		InitData(std::string descFilename, ResourceCreator* resourceCreator) :
			_filename(descFilename),
			_resourceCreator(resourceCreator)
		{

		}
	};

	void setPluginInterface(IRenderPassPlugin* pluginInterface) { _pluginInterface = pluginInterface; }

	IRenderFlowGraphIOInterface* getIOInterface() { return (IRenderFlowGraphIOInterface*)_ioInterface; }

	SlabCache& getCache() { return _cache; };

	void execute(IRenderDataGroup * collection, IGraphicsCommandBlock * commandBlock);

	IShader* getShader(std::string& name) { return _shaders.at(name); }
	IGPUPipeline* getPSO() { return dynamic_cast<IGPUPipeline*>(&_pso); }

	void rebuildPSO(IGPUPipeline* pso);

	void unload();
	void load();
};

