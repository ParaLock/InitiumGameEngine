#include "../include/RenderFlowGraph.h"



RenderFlowGraph::RenderFlowGraph()
{
	_resourceGroupByType.insert({"RENDER_TARGET", "RenderTargetGroup"});
	_resourceGroupByType.insert({"TEXTURE", "TextureGroup" });
	_resourceGroupByType.insert({"TEXTURE_SAMPLER", "TextureSamplerGroup" });
	_resourceGroupByType.insert({ "DEPTH_STENCIL", "DepthStencilGroup" });
}


RenderFlowGraph::~RenderFlowGraph()
{
}

void RenderFlowGraph::registerIOInterface(RenderFlowGraphIOInterface * ioInterface)
{
	_registeredIOInterfaces.insert({ ioInterface->getParentName(), ioInterface });
}

void RenderFlowGraph::load()
{
	EventHub* hub = EventFrameworkCore::getInstance()->getGlobalEventHub("RenderFlowGraphEventHub");

	hub->subscribeListener(this);

	InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

	RenderFlowGraphParser parser;

	ParsedRenderFlowGraphData& data = parser.parseRenderFlowGraph(realBuilder->_filename, realBuilder->_resCreator);

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

			IResource* edgeResource = IResource::lookupResource(
				edge._name, 
				_resourceGroupByType.at(edge._type), 
				realBuilder->_resCreator->getParentEngine());

			coreInterface->assignHookResource(edge._type, edge._index, edgeResource);
		}
	}

	for each(ParsedRenderFlowGraphOP op in data._endsceneOps) {

		GPUPipelineOP newop;

		IResource* opTarget = IResource::lookupResource(
			op._targetName,
			_resourceGroupByType.at(op._targetType),
			realBuilder->_resCreator->getParentEngine());

		newop.opTarget = opTarget;

		EnumString<SHADER_RESOURCE_TYPE>::To(newop.resType, op._targetType);

		EnumString<PIPELINE_OP_TYPE>::To(newop.opType, op._opType);

		IGraphicsCore::getInstance()->getEndscenePSO()->attachOP(newop);
	}

}

std::list<std::string>& RenderFlowGraph::getNodeExecutionOrder()
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
