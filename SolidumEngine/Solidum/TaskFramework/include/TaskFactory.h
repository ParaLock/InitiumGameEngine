#pragma once
#include "../../sysInclude.h"

#include "../../ResourceFramework/include/ResourceFactory.h"

#include "Task.h"

class TaskFactory : public ResourceFactory<Task, TASK_TYPE>
{
private:
public:
	Task* createObject(TASK_TYPE type);
};