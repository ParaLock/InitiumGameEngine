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

	void getRenderDataByType(RENDER_DATA_TYPE type, std::list<std::shared_ptr<RenderDataPacket>>& out) { _groupItems.queryNodesByType(type, out); };
	void getAllRenderData(std::list<std::shared_ptr<RenderDataPacket>>& out) { _groupItems.queryAllNodes(out); };

	void addPacketToRenderGroup(std::shared_ptr<RenderDataPacket> packet);
	void removePacket(std::shared_ptr<RenderDataPacket> packet);

	void setGlobalData(RenderData_GlobalData gData) { _globalData = gData; };
	RenderData_GlobalData* getGlobalData() { return &_globalData; }
};

