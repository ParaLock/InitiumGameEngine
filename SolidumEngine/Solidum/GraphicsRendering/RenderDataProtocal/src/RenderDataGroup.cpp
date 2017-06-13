#include "../include/RenderDataGroup.h"



RenderDataGroup::RenderDataGroup()
{
}


RenderDataGroup::~RenderDataGroup()
{
}

void RenderDataGroup::addPacketToRenderGroup(std::shared_ptr<RenderDataPacket> packet)
{
	_groupItems.addNode(packet);
}
