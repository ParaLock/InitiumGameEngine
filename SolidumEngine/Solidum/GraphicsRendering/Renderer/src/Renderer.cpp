#include "../include/Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData *realBuilder = static_cast<InitData*>(builder.get());
	
	_renderGraph = new RenderFlowGraph();
	_renderGraph->load(std::make_shared<RenderFlowGraph::InitData>(realBuilder->_renderGraphFilename));

	syncWithGraph();

}

void Renderer::renderScene(GraphicsCommandList * commandList, RenderDataGroup * collection)
{
	for each(std::shared_ptr<RenderPassWrapper> renderPass in _activeRenderOrder) {
		renderPass->execute(commandList, collection);
	}
}

void Renderer::syncWithGraph()
{
	_activeRenderOrder.clear();

	auto& renderOrder = _renderGraph->getNodeExecutionOrder();

	for each(std::string rendererName in renderOrder) {

		std::shared_ptr<RenderPassWrapper> activeRenderer = IGraphicsCore::getInstance()->getRegisteredRenderPass(rendererName);
		_activeRenderOrder.push_back(activeRenderer);
	}
}
