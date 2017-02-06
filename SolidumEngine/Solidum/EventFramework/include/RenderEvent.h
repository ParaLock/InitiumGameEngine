#pragma once

#include "IEvent.h"

#include "../../GraphicsRendering/Transform/include/Transform.h"

#include "../../GraphicsRendering/RenderDataStream/include/RenderDataStream.h"

class RenderEvent : public IEvent
{
private:
	RenderDataStream* _stream = nullptr;
	std::string _rendProcID;
public:
	RenderEvent(EVENT_TYPE type);
	~RenderEvent();

	void setData(RenderDataStream* data, std::string renderProcID) { _stream = data; _rendProcID = renderProcID; }

	RenderDataStream* getStream() { return _stream; }
	std::string getRendProcID() { return _rendProcID; };
};

