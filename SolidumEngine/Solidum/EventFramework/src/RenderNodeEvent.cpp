#include "../include/RenderNodeEvent.h"



RenderNodeEvent::RenderNodeEvent(SUB_EVENT_TYPE subType, RenderNode* node, uint64_t nodeid)
{
	_type = EVENT_TYPE::GRAPHICS_EVENT;
	_subType = subType;

	_node = node;
	_nodeid = nodeid;
}


RenderNodeEvent::~RenderNodeEvent()
{
}
