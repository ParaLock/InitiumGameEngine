#pragma once
#include "../../../sysInclude.h"

#include "../../../MemoryManagement/include/SlabCache.h"

#include "RenderDataAttribs.h"

struct RenderData {

	RenderDataAttributes attribs;

	SlabCache::Slab* _slab;
};

class RenderDataPacket
{
private:
	RENDER_DATA_TYPE _type;

	RenderData _data;

	SlabCache* _cache;
public:
	RenderDataPacket(SlabCache* cache);
	~RenderDataPacket();

	template<typename T>
	void addData(T* data) { 
		
		RenderData packetCore;

		SlabCache::Slab* dataSlab = _cache->getSlab(sizeof(T));

		T* buffPtr = (T*)dataSlab->_mem;

		*buffPtr = *data;

		packetCore._slab = dataSlab;

		_data = packetCore;
	};

	template<typename T>
	T* getData() {

		return (T*)_data._slab->_mem;
	};

	RenderDataAttributes& getAttributes() { return _data.attribs; }

	void setType(RENDER_DATA_TYPE type) { _type = type; };

	RENDER_DATA_TYPE getType() { return _type; };
};

