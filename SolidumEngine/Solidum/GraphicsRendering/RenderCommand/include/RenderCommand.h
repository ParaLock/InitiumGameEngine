#pragma once
#include "../../../sysInclude.h"

class RenderCommand
{
private:
	uint32_t flags = 0;
public:
	RenderCommand();
	~RenderCommand();

	virtual void execute() = 0;
};

