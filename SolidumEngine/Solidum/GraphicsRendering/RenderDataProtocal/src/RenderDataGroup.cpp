#include "../include/RenderDataGroup.h"

RenderDataGroup::RenderDataGroup(SlabCache * cache)
{

	_cache = cache;
}

RenderDataGroup::~RenderDataGroup()
{
}
void RenderDataGroup::removePacket(std::shared_ptr<RenderDataPacket> packet)
{
	_groupItems.removeNode(packet);
}
