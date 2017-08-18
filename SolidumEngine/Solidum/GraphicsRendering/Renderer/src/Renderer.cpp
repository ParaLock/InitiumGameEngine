#include "../include/Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::load()
{
	InitData *realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

	_renderGraph = (RenderFlowGraph*)realBuilder->_resCreator->createResourceImmediate<RenderFlowGraph>(&RenderFlowGraph::InitData(realBuilder->_renderGraphFilename, realBuilder->_resCreator), "",
		[](IResource*) {});

	syncWithGraph();

}

void Renderer::renderScene(GraphicsCommandList * commandList, RenderDataGroup * collection)
{
	int cmdBlockCount = 0;

	PerfProfiler profiler;

	RenderDataGroup processedCollection = *collection;

	processedCollection = performGeneralRenderDataProcessing(processedCollection);

	for each(RenderPassPluginWrapper* renderPass in _activeRenderOrder) {

		profiler.start();

		auto* cmdBlock = commandList->getNextCmdBlock(cmdBlockCount);

		renderPass->execute(&processedCollection, cmdBlock);

		profiler.end("Renderer: RenderPass: " + renderPass->name() + " ");

		cmdBlockCount++;
	}
}

void Renderer::pushGeneralProcessingLayer(std::shared_ptr<RenderDataProcessingLayer> layer)
{
	_generalProcessingLayerStack.push_back(layer);
}

RenderDataGroup& Renderer::performGeneralRenderDataProcessing(RenderDataGroup& data)
{
	for each(std::shared_ptr<RenderDataProcessingLayer> layer in _generalProcessingLayerStack) {

		layer->execute(data);
	}

	return data;
}

void Renderer::syncWithGraph()
{
	_activeRenderOrder.clear();

	auto& renderOrder = _renderGraph->getNodeExecutionOrder();

	for each(std::string rendererName in renderOrder) {

		RenderPassPluginWrapper* activeRenderer = IGraphicsCore::getInstance()->getRegisteredRenderPass(rendererName);
		_activeRenderOrder.push_back(activeRenderer);
	}
}
