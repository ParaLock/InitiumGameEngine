#include "../include/RenderDataPacket.h"

void RenderDataPacket::free()
{
	_cache->free(_data);
}
