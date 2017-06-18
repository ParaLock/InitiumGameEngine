#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../Shaders/include/ShaderParser.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../Shaders/include/Shader.h"

#include "../../RenderPass/include/RenderPassWrapper.h"

#include "../../RenderDataProcessingLayers/include/RenderDataProcessingLayer.h"

class Renderer : public IResource
{
private:
	std::list<std::shared_ptr<RenderDataProcessingLayer>> _generalProcessingLayerStack;

	std::list<std::shared_ptr<RenderPassWrapper>> _activeRenderOrder;

	RenderFlowGraph* _renderGraph;

	std::string _name;

	virtual void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
	
	RenderDataGroup& performGeneralRenderDataProcessing(RenderDataGroup& collection);

protected:
public:
	Renderer();
	~Renderer();

	struct InitData : public IResourceBuilder {
		
		std::string _renderGraphFilename;

		InitData(std::string renderGraphFilename) :
			_renderGraphFilename(renderGraphFilename)
		{

		}
	};

	void pushGeneralProcessingLayer(std::shared_ptr<RenderDataProcessingLayer> layer);

	void load(std::shared_ptr<IResourceBuilder> builder);

	void renderScene(GraphicsCommandList* commandList, RenderDataGroup* collection);

	void syncWithGraph();

	std::string getName() { return _name; }
};

