#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../Shaders/include/ShaderParser.h"

#include "../../Shaders/include/Shader.h"

#include "../../RenderPass/include/RenderPassPluginWrapper.h"

#include "../../RenderDataProcessingLayers/include/RenderDataProcessingLayer.h"

class GenericFactory;
class ResourcePool;

class Renderer : public Resource<Renderer, GenericFactory, ResourcePool>
{
private:
	std::list<std::shared_ptr<RenderDataProcessingLayer>> _generalProcessingLayerStack;

	std::list<RenderPassPluginWrapper*> _activeRenderOrder;

	RenderFlowGraph* _renderGraph;

	std::string _name;

	virtual void unload() {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
	
	RenderDataGroup& performGeneralRenderDataProcessing(RenderDataGroup& collection);

protected:
public:
	Renderer();
	~Renderer();

	struct InitData : public ResourceInitParams {
		
		InitData() {}
		

		std::string _renderGraphFilename;

		ResourceCreator* _resCreator;

		InitData(std::string renderGraphFilename, ResourceCreator* resCreator) :
			_renderGraphFilename(renderGraphFilename),
			_resCreator(resCreator)
		{

		}
	};

	void pushGeneralProcessingLayer(std::shared_ptr<RenderDataProcessingLayer> layer);

	void load();

	void renderScene(GraphicsCommandList* commandList, RenderDataGroup* collection);

	void syncWithGraph();

	std::string getName() { return _name; }

protected:
};

