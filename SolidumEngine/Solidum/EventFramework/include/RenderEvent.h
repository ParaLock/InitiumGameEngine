#pragma once

#include "IEvent.h"

#include "../../GraphicsRendering/RenderOP/include/RenderOP.h"

#include "../../GraphicsRendering/Transform/include/Transform.h"

class RenderEvent : public IEvent
{
private:
	RenderOP* _op;
public:
	RenderEvent(EVENT_TYPE type);
	~RenderEvent();

	void setRenderOP(RenderOP* op) { _op = op; }

	RenderOP* getRenderOP() { return _op; }
};

