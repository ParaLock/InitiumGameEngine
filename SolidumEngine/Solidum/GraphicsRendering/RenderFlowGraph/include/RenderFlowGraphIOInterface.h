#pragma once
#include "../../../EventFramework/include/EventFrameworkCore.h"
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/EventHub.h"

#include "../../../EventFramework/include/Event.h"

#include "../../../ResourceFramework/include/Resource.h"
#include "../../../sysInclude.h"

struct RenderFlowGraphNodeIOHook {
	std::string _name;
	std::string _type;

	void* _userData;

	int _index;
	bool _isOutput;

	IResource* _res = nullptr;
};

typedef std::map<std::string, std::map<int, RenderFlowGraphNodeIOHook*>> HookMapsByHookType;

class RenderFlowGraphIOInterface : public IEventListener
{
protected:
	std::string _parentName;

	HookMapsByHookType _hookMaps;
	std::map<std::string, RenderFlowGraphNodeIOHook*> _hooksByName;
public:
	RenderFlowGraphIOInterface();
	~RenderFlowGraphIOInterface();

	void setParentName(std::string& name) { _parentName = name; };
	std::string& getParentName() { return _parentName; }

	void addResourceHook(RenderFlowGraphNodeIOHook hook);

	void assignHookResource(std::string type, int index, IResource* res);

	void assignHookResourceByName(std::string hookName, IResource* res);

	std::list<RenderFlowGraphNodeIOHook*> getLiveHooks();

	void onEvent(EVENT_PTR evt);
};

enum RENDER_FLOW_GRAPH_EVENT_SUB_EVENT {
	IO_INTERFACE_QUERY,
	IO_INTERFACE_QUERY_RESPONSE
};

struct RenderFlowGraphIOInterfaceEvtData : public EventData {
	std::function<void(RenderFlowGraphIOInterface*)> _registerIOInterfaceCallback;

	RENDER_FLOW_GRAPH_EVENT_SUB_EVENT _subEvent;

	std::string _targetGraphName;
	std::string _targetIOInterfaceName;
};


