#include "../include/RenderDataGroup.h"

RenderDataGroup::RenderDataGroup(SlabCache* cache)
{
	_cache = cache;
}

RenderDataGroup::~RenderDataGroup()
{
	for each(RenderDataPacket data in _dataStore) {
		data.free();
	}

	_dataStore.clear();
}

void RenderDataGroup::removePacket(RenderDataPacket& packet)
{
	_groupItems.removeNode(&packet);
}
