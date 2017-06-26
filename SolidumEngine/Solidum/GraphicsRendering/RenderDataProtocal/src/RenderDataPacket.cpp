#include "../include/RenderDataPacket.h"


RenderDataPacket::RenderDataPacket(SlabCache * cache)
{
	_cache = cache;
}

RenderDataPacket::~RenderDataPacket()
{
	_cache->free(_data._slab);
}
