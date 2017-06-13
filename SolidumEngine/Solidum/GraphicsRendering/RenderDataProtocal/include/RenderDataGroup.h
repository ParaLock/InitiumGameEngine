#pragma once
#include "../../../sysInclude.h"

#include "../../SpatialAccelerationStructures/include/TypeOptimizedTree.h"

#include "RenderDataPacket.h"

class RenderDataGroup
{
private:
	TypeOptimizedTree<
		RenderDataPacket,
		RENDER_DATA_TYPE
	> _groupItems;

	RenderData_GlobalData _globalData;

public:
	RenderDataGroup();
	~RenderDataGroup();

	std::list<std::shared_ptr<RenderDataPacket>> getRenderDataByType(RENDER_DATA_TYPE type) { return _groupItems.queryNodesByType(type); };

	void addPacketToRenderGroup(std::shared_ptr<RenderDataPacket> packet);

	void setGlobalData(RenderData_GlobalData gData) { _globalData = gData; };
	RenderData_GlobalData* getGlobalData() { return &_globalData; }
};

