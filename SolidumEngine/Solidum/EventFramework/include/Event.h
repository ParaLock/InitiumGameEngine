#pragma once
#include "../../sysInclude.h"

enum EVENT_TYPE {
	INPUT_EVENT,
	ENTITY_EVENT,
	PHYSICS_EVENT,
	GRAPHICS_EVENT,
	RENDER_FLOW_GRAPH_EVENT
};


class EventData {
private:
public:
};

class Event
{
private:
	EVENT_TYPE _type;
	std::shared_ptr<EventData> _dataPtr;
public:
	Event();
	~Event();

	EVENT_TYPE getType() { return _type; }
	void setType(EVENT_TYPE type) { _type = type; }

	std::shared_ptr<EventData> getData() { return _dataPtr; }
	void setData(std::shared_ptr<EventData> data) { _dataPtr = data; }
};

