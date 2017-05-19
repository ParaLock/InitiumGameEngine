#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../RenderNodeTree/include/IRenderNodeTree.h"
#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../Shaders/include/ShaderParser.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "RendererDescriptorParser.h"

#include "../../Shaders/include/Shader.h"

class Renderer : public IResource
{
private:
	virtual void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName);

protected:
	RENDERER_TYPE _type;
	
	std::string _name;

	std::map<std::string, IShader*> _shaders;

	GPUPipeline* _pipelineState;

	GPUPipeline* rebuildPSO();

	RenderFlowGraphIOInterface* _ioInterface;
public:
	Renderer();
	~Renderer();

	struct InitData : public IResourceBuilder {
		
		std::string _filename;

		InitData(std::string descFilename) : 
			_filename(descFilename) 
		{

		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);

	virtual void gatherAndPrepareNodes(IRenderNodeTree* tree) = 0;
	virtual void processNodes(GraphicsCommandList* commandList) = 0;

	virtual void DeferredInit() {};

	std::string getName() { return _name; }

	RenderFlowGraphIOInterface* getIOInterface() { return _ioInterface; };
};

