#include "../include/RenderDataGroup.h"

RenderDataGroup::RenderDataGroup(SlabCache* cache)
{
	_cache = cache;
}

RenderDataGroup::~RenderDataGroup()
{
}

void RenderDataGroup::removePacket(RenderDataPacket& packet)
{
	_groupItems.removeNode(&packet);
}

void RenderDataGroup::freeRenderPackets()
{
	for each(RenderDataPacket data in _dataStore) {
		data.free();
	}

	_dataStore.clear();
}
