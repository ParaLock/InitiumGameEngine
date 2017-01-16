#include "../include/RenderQueue.h"



RenderQueue::RenderQueue()
{
}


RenderQueue::~RenderQueue()
{
}

void RenderQueue::enqueueLight(Light* light)
{
	_lights.push_back(light);
}

void RenderQueue::enqueueSoldiumObject(SolidumObject* obj)
{
	_objects.push_back(obj);
}

std::list<Light*>& RenderQueue::getLightQueue()
{
	return _lights;
}

std::list<SolidumObject*>& RenderQueue::getSolidumObjectQueue()
{
	return _objects;
}
