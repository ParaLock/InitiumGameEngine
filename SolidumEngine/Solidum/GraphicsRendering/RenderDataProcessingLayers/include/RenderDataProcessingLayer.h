#pragma once
#include "../../RenderDataProtocal/include/RenderDataGroup.h"

class RenderDataProcessingLayer
{
public:
	RenderDataProcessingLayer();
	~RenderDataProcessingLayer();

	virtual void execute(RenderDataGroup& data) = 0;
};

