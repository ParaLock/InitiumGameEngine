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

void RenderQueue::queueRenderOP(RenderOP renderOP)
{
	if(renderOP.getMesh() != nullptr)
		_queuedModels->push_back(renderOP);
	if (renderOP.getLight() != nullptr)
		_queuedLights->push_back(renderOP);
}

void RenderQueue::processQueuedItems(std::function<void(RenderOP)> callback)
{
	auto mItr = _queuedModels->begin();
	auto lItr = _queuedLights->begin();

	while(mItr != _queuedModels->end()) {
		callback(*mItr);

		mItr = _queuedModels->erase(mItr);
	}

	while(lItr != _queuedLights->end()) {
		callback(*lItr);

		lItr = _queuedLights->erase(lItr);
	}
}

