#include "../include/RenderFlowGraphIOInterface.h"



RenderFlowGraphIOInterface::RenderFlowGraphIOInterface()
{
	EventFrameworkCore::getInstance()->getGlobalEventHub("RenderFlowGraphEventHub")->subscribeListener(this);
}


RenderFlowGraphIOInterface::~RenderFlowGraphIOInterface()
{
}

void RenderFlowGraphIOInterface::addResourceHook(RenderFlowGraphNodeIOHook hook)
{
	RenderFlowGraphNodeIOHook* newHook = new RenderFlowGraphNodeIOHook();
	
	newHook->_res = nullptr;

	if (_hookMaps.find(hook._type) == _hookMaps.end()) {
		_hookMaps.insert({ hook._type, std::map<int, RenderFlowGraphNodeIOHook*>() });
	}

	auto& _hooksByIndex = _hookMaps.at(hook._type);

	*newHook = hook;

	_hooksByName.insert({ newHook->_name, newHook });

	_hooksByIndex.insert({ hook._index, newHook });
}

void RenderFlowGraphIOInterface::assignHookResource(std::string type, int index, IResource * res)
{
	if (_hookMaps.find(type) != _hookMaps.end()) {

		auto& _hooksByIndex = _hookMaps.at(type);

		if (_hooksByIndex.find(index) != _hooksByIndex.end()) {
			RenderFlowGraphNodeIOHook* hook = _hooksByIndex.at(index);

			hook->_res = res;
		}
	}
}

void RenderFlowGraphIOInterface::assignHookResourceByName(std::string hookName, IResource * res)
{

	if (_hooksByName.find(hookName) != _hooksByName.end()) {

		RenderFlowGraphNodeIOHook* hook = _hooksByName.at(hookName);

		hook->_res = res;
	}
}

std::list<RenderFlowGraphNodeIOHook*> RenderFlowGraphIOInterface::getLiveHooks()
{
	std::list<RenderFlowGraphNodeIOHook*> _usedHooks;

	HookMapsByHookType::iterator hookMapItr = _hookMaps.begin();

	while(hookMapItr != _hookMaps.end()) {

		std::map<int, RenderFlowGraphNodeIOHook*> hooksByIndexMap = hookMapItr->second;

		std::map<int, RenderFlowGraphNodeIOHook*>::iterator hooksByIndexMapItr = hooksByIndexMap.begin();

		while(hooksByIndexMapItr != hooksByIndexMap.end()) {

			RenderFlowGraphNodeIOHook* hook = hooksByIndexMapItr->second;

			if (hook->_res != nullptr)
				_usedHooks.push_back(hook);

			hooksByIndexMapItr++;
		}

		hookMapItr++;
	}

	return _usedHooks;
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
