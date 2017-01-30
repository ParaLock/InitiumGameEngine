#include "../include/RenderQueue.h"



RenderQueue::RenderQueue()
{
	_queuedLights = new RENDER_QUEUE;
	_queuedModels = new RENDER_QUEUE;
}


RenderQueue::~RenderQueue()
{
	delete _queuedLights;
	delete _queuedModels;
}

void RenderQueue::queueRenderOP(RenderOP * renderOP)
{
	if(renderOP->getMesh() != nullptr)
		_queuedModels->push_back(renderOP);
	if (renderOP->getLight() != nullptr)
		_queuedLights->push_back(renderOP);
}

void RenderQueue::dequeueRenderOP(RenderOP * renderOP)
{
}

RENDER_QUEUE RenderQueue::getRenderQueue()
{
	RENDER_QUEUE sortedQueue;

	for (auto itr = _queuedModels->begin(); itr != _queuedModels->end(); itr++) {
		sortedQueue.push_back(*itr);
	}
	for (auto itr = _queuedLights->begin(); itr != _queuedLights->end(); itr++) {
		sortedQueue.push_back(*itr);
	}

	return sortedQueue;
}
