#pragma once
#include "../../../sysInclude.h"

class Light;
class SolidumObject;

class RenderQueue
{
private:
	std::list<Light*> _lights;
	std::list<SolidumObject*> _objects;
public:
	RenderQueue();
	~RenderQueue();

	void enqueueLight(Light* light);
	void enqueueSoldiumObject(SolidumObject* obj);

	std::list<Light*>& getLightQueue();
	std::list<SolidumObject*>& getSolidumObjectQueue();
};

