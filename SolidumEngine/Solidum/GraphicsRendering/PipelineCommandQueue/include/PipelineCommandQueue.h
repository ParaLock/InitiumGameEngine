#pragma once
#include "../../../sysInclude.h"

#include "../../PipelineCommand/include/PipelineCommand.h"

class PipelineCommandQueue
{
private:
	std::vector<PipelineCommand*>* _queue;
public:
	PipelineCommandQueue();
	~PipelineCommandQueue();

	void queueCommand(PipelineCommand* command);

	void processAllCommands();
};

