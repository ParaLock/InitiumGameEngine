#pragma once
#include "../../../sysInclude.h"

#include "../../SpatialAccelerationStructures/include/TypeOptimizedTree.h"

#include "../../RenderDataProtocal/include/RenderDataPacket.h"

struct RenderDataAttributes;

class RenderDataGroup
{
private:

	std::list<RenderDataPacket> _dataStore;

	TypeOptimizedTree<
		RenderDataPacket*,
		RENDER_DATA_TYPE
	> _groupItems;

	RenderData_GlobalData _globalData;

	SlabCache* _cache;

public:
	RenderDataGroup(SlabCache* cache);
	~RenderDataGroup();

	void getRenderDataByType(RENDER_DATA_TYPE type, std::list<RenderDataPacket*>& out) { _groupItems.queryNodesByType(type, out); };
	void getAllRenderData(std::list<RenderDataPacket*>& out) { _groupItems.queryAllNodes(out); };

	template<typename T>
	void addRenderData(T* data, RENDER_DATA_TYPE type, RenderDataAttributes* attributes) {
	
		_dataStore.push_back(RenderDataPacket(_cache));

		RenderDataPacket* packet = &_dataStore.back();

		packet->addData<T>(data);
		
		packet->setType(type);

		packet->setAttributes(*attributes);

		_groupItems.addNode(packet);
		
	}

	void removePacket(RenderDataPacket& packet);

	void setGlobalData(RenderData_GlobalData& gData) { _globalData = gData; };
	RenderData_GlobalData* getGlobalData() { return &_globalData; }

	void freeRenderPackets();
};

