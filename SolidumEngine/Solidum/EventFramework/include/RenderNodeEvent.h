#pragma once
#include "../../sysInclude.h"

#include "IEvent.h"

class RenderNode;

class RenderNodeEvent : public IEvent
{
private:
	RenderNode* _node;
	uint64_t _nodeid;
public:
	RenderNodeEvent(SUB_EVENT_TYPE subType, RenderNode* node, uint64_t nodeid);
	~RenderNodeEvent();

	void setNode(RenderNode* node) { _node = node; }
	void setNodeID(uint64_t nodeid) { _nodeid = nodeid; }

	RenderNode* getNode() { return _node; }
	uint64_t getNodeID() { return _nodeid; }
};

