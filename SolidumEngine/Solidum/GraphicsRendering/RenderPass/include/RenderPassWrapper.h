#pragma once
#include "../../../ResourceFramework/include/IResource.h"
#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"
#include "../../GraphicsCommandList/include/GraphicsCommandList.h"
#include "../../RenderDataProtocal/include/RenderDataGroup.h"
#include "../../../sysInclude.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Shaders/include/ShaderParser.h"
#include "../../Shaders/include/Shader.h"
#include "../../Shaders/include/IShader.h"

#include "RenderPassDescriptorParser.h"

class RenderPassWrapper : public IResource
{
private:
	std::string _name;

	std::map<std::string, IShader*> _shaders;

	virtual void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	RenderFlowGraphIOInterface* _ioInterface;

	std::function<void(GraphicsCommandList*, RenderDataGroup&, RenderPassWrapper*)> _renderPassCallback;
public:
	RenderPassWrapper();
	~RenderPassWrapper();

	struct InitData : public IResourceBuilder {

		std::string _filename;

		InitData(std::string descFilename) :
			_filename(descFilename)
		{

		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);

	void setRenderPass(
		std::function<void(GraphicsCommandList*, RenderDataGroup&, RenderPassWrapper*)> func)
	{
		_renderPassCallback = func;
	};

	void execute(GraphicsCommandList* commandList, RenderDataGroup& collection);

	RenderFlowGraphIOInterface* getIOInterface() { return _ioInterface; };

	IShader* getShader(std::string shaderName) { return _shaders.at(shaderName); }

	GPUPipeline* rebuildPSO(GPUPipeline* pipeline);

	std::string getName() { return _name; }
};

