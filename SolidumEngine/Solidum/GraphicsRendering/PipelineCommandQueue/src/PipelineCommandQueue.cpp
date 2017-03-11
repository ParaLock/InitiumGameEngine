#include "../include/PipelineCommandQueue.h"



PipelineCommandQueue::PipelineCommandQueue()
{
	_queue = new std::vector<PipelineCommand*>;
}


PipelineCommandQueue::~PipelineCommandQueue()
{
	delete _queue;
}

void PipelineCommandQueue::queueCommand(PipelineCommand* command)
{
	_queue->push_back(command);
}

void PipelineCommandQueue::processAllCommands()
{
	auto itr = _queue->begin();

	while(itr != _queue->end()) {

		PipelineCommand* command = *itr;

		command->execute();

		delete command;

		itr++;
	}

	_queue->clear();
}
