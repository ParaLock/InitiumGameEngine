#pragma once
#include "../../../sysInclude.h"

#include "../../SpatialAccelerationStructures/include/TypeOptimizedTree.h"

#include "../../../MemoryManagement/include/SlabCache.h"

#include "RenderDataPacket.h"

class RenderDataGroup
{
private:
	TypeOptimizedTree<
		RenderDataPacket,
		RENDER_DATA_TYPE
	> _groupItems;

	RenderData_GlobalData _globalData;
	SlabCache* _cache;

public:
	RenderDataGroup(SlabCache* cache);
	~RenderDataGroup();

	void getRenderDataByType(RENDER_DATA_TYPE type, std::list<std::shared_ptr<RenderDataPacket>>& out) { _groupItems.queryNodesByType(type, out); };
	void getAllRenderData(std::list<std::shared_ptr<RenderDataPacket>>& out) { _groupItems.queryAllNodes(out); };

	template<typename T>
	void addRenderData(T* data, RENDER_DATA_TYPE type, RenderDataAttributes* attributes) {
	
		std::shared_ptr<RenderDataPacket> dataPtr = std::make_shared<RenderDataPacket>(_cache);

		dataPtr->addData<T>(data);
		dataPtr->setType(type);

		_groupItems.addNode(dataPtr);
		
	}

	void removePacket(std::shared_ptr<RenderDataPacket> packet);

	void setGlobalData(RenderData_GlobalData gData) { _globalData = gData; };
	RenderData_GlobalData* getGlobalData() { return &_globalData; }
};

