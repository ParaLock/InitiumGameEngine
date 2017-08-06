#pragma once
#include "../../../sysInclude.h"

#include "../../../MemoryManagement/include/SlabCache.h"

#include "RenderDataAttribs.h"

class RenderDataPacket 
{
private:
	SlabCache* _cache;

	RENDER_DATA_TYPE _type;

	RenderDataAttributes _attribs;

	Slab* _data;
public:

	RenderDataPacket(SlabCache* cache) { _cache = cache; };
	~RenderDataPacket() {};

	RenderDataPacket(const RenderDataPacket& other) {

		_data = other._data;
		_attribs = other._attribs;
		_type = other._type;

		_cache = other._cache;
	}

	template<typename T_DATA>
	void addData(T_DATA* data) { 
	
		_data = _cache->getSlab(sizeof(T_DATA));

		T_DATA* slabData = static_cast<T_DATA*>(_data->_mem);

		*slabData = *data;
	};
	
	void* getData() { return _data->_mem; }

	RenderDataAttributes& getAttributes() { return _attribs; }
	void setAttributes(RenderDataAttributes& attribs) { _attribs = attribs; }

	void setType(RENDER_DATA_TYPE type) { _type = type; };
	RENDER_DATA_TYPE getType() { return _type; };

	void free();
};

