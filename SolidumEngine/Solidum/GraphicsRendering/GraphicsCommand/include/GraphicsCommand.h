#pragma once
class GraphicsCommand
{
private:
	uint64_t _executionThreadID;
public:
	GraphicsCommand();
	~GraphicsCommand();

	virtual void execute() = 0;
};

