#pragma once
#include "RenderDataProcessingLayer.h"

class FrustumCullingLayer : public RenderDataProcessingLayer
{
private:
public:
	FrustumCullingLayer();
	~FrustumCullingLayer();

	void execute(RenderDataGroup& data);
};

