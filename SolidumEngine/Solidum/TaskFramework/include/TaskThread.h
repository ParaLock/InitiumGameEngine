#pragma once
#include "../../sysInclude.h"

#include "Task.h"

class TaskThread
{
private:
	volatile bool _running = false;

	std::thread _executionThread;

	std::mutex _queueLock;

	std::list<Task*> _newTaskBuffer;
	std::list<Task*> _workqueue;
public:
	TaskThread();
	~TaskThread();

	void start();
	void stop();

	void queueTask(Task* task);

	void processPendingTasks();

	bool isRunning();
};

