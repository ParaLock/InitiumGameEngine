#include "../include/GraphicsCommandQueue.h"



GraphicsCommandQueue::GraphicsCommandQueue()
{
	_queue = new std::list<GraphicsCommand*>;
}


GraphicsCommandQueue::~GraphicsCommandQueue()
{
	delete _queue;
}

void GraphicsCommandQueue::queueCommand(GraphicsCommand * command)
{
	_queue->push_back(command);
}

void GraphicsCommandQueue::processCommands()
{
	auto itr = _queue->begin();

	while (itr != _queue->end()) {

		GraphicsCommand* command = *itr;

		command->execute();

		delete command;

		itr = _queue->erase(itr);
	}
}