#pragma once
#include "../../../ResourceFramework/include/Resource.h"
#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"
#include "../../GraphicsCommandList/include/GraphicsCommandList.h"
#include "../../RenderDataProtocal/include/RenderDataGroup.h"
#include "../../../sysInclude.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Shaders/include/ShaderParser.h"
#include "../../Shaders/include/Shader.h"
#include "../../Shaders/include/IShader.h"

#include "RenderPassDescriptorParser.h"

class GenericFactory;
class ResourcePool;

class RenderPassWrapper : public Resource<RenderPassWrapper, GenericFactory, ResourcePool>
{
private:

	SlabCache _generalPurposeSlabcache;

	std::string _name;

	std::map<std::string, IShader*> _shaders;

	virtual void unload() { };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	RenderFlowGraphIOInterface* _ioInterface;

	std::function<void(GraphicsCommandList*, RenderDataGroup&, RenderPassWrapper*)> _renderPassCallback;
public:
	RenderPassWrapper();
	~RenderPassWrapper();

	static const unsigned int TYPE = 0;

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

	void load();

	void setRenderPass(
		std::function<void(GraphicsCommandList*, RenderDataGroup&, RenderPassWrapper*)> func)
	{
		_renderPassCallback = func;
	};

	void execute(GraphicsCommandList* commandList, RenderDataGroup& collection);

	RenderFlowGraphIOInterface* getIOInterface() { return _ioInterface; };

	IShader* getShader(std::string shaderName) { return _shaders.at(shaderName); }

	GPUPipeline* rebuildPSO(GPUPipeline* pipeline);

	SlabCache& getSlabCache() { return _generalPurposeSlabcache;};

	std::string getName() { return _name; }

protected:
};

