#pragma once
#include "../common.h"

struct RenderDataAttributes;

class IRenderDataPacket {
public:
	virtual void* getData() = 0;

	virtual RenderDataAttributes& getAttributes() = 0;

	virtual RENDER_DATA_TYPE getType() = 0;

	virtual void free() = 0;
private:
};