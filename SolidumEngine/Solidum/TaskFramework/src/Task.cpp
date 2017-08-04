#include "../include/Task.h"



Task::Task()
{
}


Task::~Task()
{
}

void Task::unload()
{
	_child = nullptr;
	_parent = nullptr;

	_handle->_taskFreed = false;
	_handle->_taskComplete = true;

	_isComplete = true;

	_cyclicTask = false;
	_processed = false;

	_executionCallback = std::function<void()>();
	_completionCallback = std::function<void(std::unique_ptr<TaskCompletionStatus>)>();
}

void Task::touch()
{
	if (_isComplete && _cyclicTask) {

		_parentThreadEnqueue(this);

		start();
	}
}

void Task::execute()
{
	if (!_isComplete) {

		_handle->_taskComplete = false;
		_handle->_taskFreed = false;

		_executionCallback();

		if (_freeOnComplete) {

			stop();

			_handle->_taskFreed = true;
		}
	}
}

void Task::stop()
{
	_isComplete = true;
	_handle->_taskComplete = true;
}

void Task::setPriority(int priority)
{
	_priority = priority;
}

void Task::setExecutionCallback(std::function<void()> func)
{
	_executionCallback = func;
}

void Task::setCompletionCallback(std::function<void(std::unique_ptr<TaskCompletionStatus>)> func)
{
	_completionCallback = func;
}

int Task::getPriority()
{
	return 0;
}
