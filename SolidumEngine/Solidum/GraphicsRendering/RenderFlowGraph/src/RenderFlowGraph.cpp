#include "../include/RenderFlowGraph.h"



RenderFlowGraph::RenderFlowGraph()
{
	_managerNameByResourceTypeName.insert({"RENDER_TARGET", "RenderTargetManager"});
	_managerNameByResourceTypeName.insert({"TEXTURE", "TextureManager" });
	_managerNameByResourceTypeName.insert({"TEXTURE_SAMPLER", "TextureSamplerManager" });
	_managerNameByResourceTypeName.insert({ "DEPTH_STENCIL", "DepthStencilManager" });
}


RenderFlowGraph::~RenderFlowGraph()
{
}

void RenderFlowGraph::registerIOInterface(RenderFlowGraphIOInterface * ioInterface)
{
	_registeredIOInterfaces.insert({ ioInterface->getParentName(), ioInterface });
}

void RenderFlowGraph::load(std::shared_ptr<IResourceBuilder> builder)
{
	EventHub* hub = EventFrameworkCore::getInstance()->getGlobalEventHub("RenderFlowGraphEventHub");

	hub->subscribeListener(this);

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	RenderFlowGraphParser parser;

	ParsedRenderFlowGraphData data = parser.parseRenderFlowGraph(realBuilder->_filename);


	std::shared_ptr<RenderFlowGraphIOInterfaceEvtData> _ioInterfaceQueryEvtData = std::make_shared<RenderFlowGraphIOInterfaceEvtData>();

	_ioInterfaceQueryEvtData->_registerIOInterfaceCallback = std::bind(&RenderFlowGraph::registerIOInterface, this, std::placeholders::_1);
	_ioInterfaceQueryEvtData->_targetGraphName = _name;

	_ioInterfaceQueryEvtData->_subEvent = RENDER_FLOW_GRAPH_EVENT_SUB_EVENT::IO_INTERFACE_QUERY;

	EVENT_PTR interfaceQueryPtr = std::make_shared<Event>();

	interfaceQueryPtr->setType(EVENT_TYPE::RENDER_FLOW_GRAPH_EVENT);
	interfaceQueryPtr->setData(_ioInterfaceQueryEvtData);

	_orderedNodeNames = data._orderedNodeNames;

	for each(ParsedNodeData node in data._nodes) {

		_ioInterfaceQueryEvtData->_targetIOInterfaceName = node._coreName;

		hub->publishEvent(interfaceQueryPtr);

		if (_registeredIOInterfaces.find(node._coreName) == _registeredIOInterfaces.end()) {
			std::cout << "RenderFlowGraph IO interface not Found!" << std::endl;

			continue;
		}

		RenderFlowGraphIOInterface* coreInterface = _registeredIOInterfaces.at(node._coreName);

		for each(ParsedNodeEdge edge in node._edges) {

			auto edgeResourceManager = ResourceManagerPool::getInstance()->getResourceManager(_managerNameByResourceTypeName.at(edge._type));

			IResource* edgeResource = edgeResourceManager->getResource(edge._name);

			coreInterface->assignHookResource(edge._type, edge._index, edgeResource);
		}
	}

	for each(ParsedRenderFlowGraphOP op in data._endsceneOps) {

		GPUPipelineOP newop;

		auto opTargetManager = ResourceManagerPool::getInstance()->getResourceManager(_managerNameByResourceTypeName.at(op._targetType));

		IResource* opTarget = opTargetManager->getResource(op._targetName);

		newop.opTarget = opTarget;

		EnumString<SHADER_RESOURCE_TYPE>::To(newop.resType, op._targetType);

		EnumString<PIPELINE_OP_TYPE>::To(newop.opType, op._opType);

		IGraphicsCore::getInstance()->getEndscenePSO()->attachOP(newop);
	}

}

std::list<std::string> RenderFlowGraph::getNodeExecutionOrder()
{
	return _orderedNodeNames;
}

void RenderFlowGraph::onEvent(EVENT_PTR evt)
{
	switch (evt.get()->getType()) {

	case EVENT_TYPE::RENDER_FLOW_GRAPH_EVENT:
		RenderFlowGraphIOInterfaceEvtData* evtData = (RenderFlowGraphIOInterfaceEvtData*)evt.get()->getData().get();

		switch (evtData->_subEvent) {
		case RENDER_FLOW_GRAPH_EVENT_SUB_EVENT::IO_INTERFACE_QUERY_RESPONSE:



			break;
		}

		break;	
	}
}
