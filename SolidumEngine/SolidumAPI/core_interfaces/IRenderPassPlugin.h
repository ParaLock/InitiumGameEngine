#pragma once

#include "IPlugin.h"

#include "../core_objects/include/ResourceInitParams.h"

class IGPUPipeline;
class IShader;
class IRenderFlowGraphIOInterface;
class IResourceCreator;
class SlabCache;
class IRenderDataGroup;
class IGraphicsCommandBlock;
class IRenderPassPluginWrapper;

class IRenderPassPlugin : public IPlugin {
private:
public:

	struct InitData : public ResourceInitParams {

		InitData() {}

		IResourceCreator* _resourceCreator;

		std::string _filename;

		InitData(std::string descFilename, IResourceCreator* resourceCreator) :
			_filename(descFilename),
			_resourceCreator(resourceCreator)
		{

		}
	};

	PLUGIN_TYPE getType() { return PLUGIN_TYPE::RENDER_PASS_PLUGIN; }
	
	virtual void execute(
		IRenderDataGroup * collection,
		IGraphicsCommandBlock * commandBlock,
		IRenderPassPluginWrapper* pluginWrapper) = 0;
};