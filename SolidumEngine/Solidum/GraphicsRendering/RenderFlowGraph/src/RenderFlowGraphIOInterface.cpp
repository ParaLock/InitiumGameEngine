#include "../include/RenderFlowGraphIOInterface.h"


bool RenderFlowGraphIOInterface::isLiveHookPresent(std::list<RenderFlowGraphNodeIOHook*>& liveHooks, RenderFlowGraphNodeIOHook * hookToFind)
{
	for each(RenderFlowGraphNodeIOHook* hook in liveHooks) {
		if (hook == hookToFind)
		{
			return true;
		}
	}

	return false;
}

RenderFlowGraphIOInterface::RenderFlowGraphIOInterface()
{
	EventFrameworkCore::getInstance()->getGlobalEventHub("RenderFlowGraphEventHub")->subscribeListener(this);
}


RenderFlowGraphIOInterface::~RenderFlowGraphIOInterface()
{
}

void RenderFlowGraphIOInterface::addResourceHook(RenderFlowGraphNodeIOHook& hook)
{
	//hook._res = nullptr;

	_hookList.push_back(hook);

	if (_hookIndexMapByType.find(hook._type) == _hookIndexMapByType.end()) {

		_hookIndexMapByType.insert({ hook._type, std::map<int, RenderFlowGraphNodeIOHook*>() });

	}

	auto& hookIndexMap = _hookIndexMapByType.at(hook._type);

	hookIndexMap.insert({ hook._index, &_hookList.back() });

	_hookByName.insert({ hook._name, &_hookList.back() });
	
}

void RenderFlowGraphIOInterface::assignHookResource(std::string& type, int index, IResource * res)
{
	RenderFlowGraphNodeIOHook* hook = nullptr;

	if (_hookIndexMapByType.find(type) != _hookIndexMapByType.end()) {

		auto& hookIndexMap = _hookIndexMapByType.at(type);

		hook = hookIndexMap.at(index);

		hook->_res = res;

	}
	else {
		std::cout << "RenderFlowGraphIOInterface: Resource Hook not found at resource designation: Hook index: " 
			<< std::to_string(index) << " Hook Type: " << type;
	}

	if (!isLiveHookPresent(_liveHookList, hook)) { _liveHookList.push_back(hook); }
}

void RenderFlowGraphIOInterface::assignHookResourceByName(std::string& hookName, IResource * res)
{
	auto* hook = _hookByName.at(hookName);

	if(!isLiveHookPresent(_liveHookList, hook)) { _liveHookList.push_back(hook); }

	hook->_res = res;
}

std::list<RenderFlowGraphNodeIOHook*>& RenderFlowGraphIOInterface::getLiveHooks()
{
	return _liveHookList;
}

void RenderFlowGraphIOInterface::onEvent(EVENT_PTR evt)
{
	switch (evt.get()->getType()) {
	case EVENT_TYPE::RENDER_FLOW_GRAPH_EVENT:

		RenderFlowGraphIOInterfaceEvtData* evtData = static_cast<RenderFlowGraphIOInterfaceEvtData*>(evt.get()->getData().get());

		switch (evtData->_subEvent) {
		case RENDER_FLOW_GRAPH_EVENT_SUB_EVENT::IO_INTERFACE_QUERY:

			if (evtData->_targetIOInterfaceName == _parentName) {

				evtData->_registerIOInterfaceCallback(this);

			}

			break;
		}

		break;
	}
}
