#include "../include/GraphicsCommandListQueue.h"



GraphicsCommandListQueue::GraphicsCommandListQueue()
{
	_queue = new std::list<GraphicsCommandList*>;
}


GraphicsCommandListQueue::~GraphicsCommandListQueue()
{
	delete _queue;
}

void GraphicsCommandListQueue::queueCommandList(GraphicsCommandList * command)
{
	_queue->push_back(command);
}

void GraphicsCommandListQueue::processAllCommands()
{
	auto itr = _queue->begin();

	while (itr != _queue->end()) {

		GraphicsCommandList* commandList = *itr;

		commandList->loadCommands();
		commandList->executeCommands();

		delete commandList;

		itr = _queue->erase(itr);
	}
}