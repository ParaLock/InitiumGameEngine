#include "../include/TaskFactory.h"

Task * TaskFactory::createObject(TASK_TYPE type)
{
	Task* newTask = nullptr;

	switch (type)
	{
	case TASK_TYPE::NORMAL_TASK:
		newTask = new Task();
		break;
	default:
		break;
	}

	return newTask;
}
