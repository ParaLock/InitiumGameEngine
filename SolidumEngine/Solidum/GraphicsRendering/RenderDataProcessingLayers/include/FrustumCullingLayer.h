#pragma once
#include "../../RenderDataProtocal/include/RenderDataPacket.h"

#include "RenderDataProcessingLayer.h"

class FrustumCullingLayer : public RenderDataProcessingLayer
{
private:
public:
	FrustumCullingLayer();
	~FrustumCullingLayer();

	void execute(RenderDataGroup& data);
};

