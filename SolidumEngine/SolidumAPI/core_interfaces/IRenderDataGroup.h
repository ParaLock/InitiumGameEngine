#pragma once

class IRenderDataPacket;
struct RenderData_GlobalData;

class IRenderDataGroup {
public:

	virtual void getRenderDataByType(RENDER_DATA_TYPE type, std::list<IRenderDataPacket*>& out) = 0;
	virtual void getAllRenderData(std::list<IRenderDataPacket*>& out) = 0;

	virtual void setGlobalData(RenderData_GlobalData& gData) = 0;
	virtual RenderData_GlobalData* getGlobalData() = 0;
};