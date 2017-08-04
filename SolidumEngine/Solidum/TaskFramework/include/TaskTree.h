#pragma once
#include "../../sysInclude.h"

#include "../../ResourceFramework/include/ResourcePool.h"

#include "../../ResourceFramework/include/ResourceCreator.h"

#include "TaskThread.h"

#include "Task.h"

class TaskFactory;

class TaskTree
{
private:
	int _numTasks = 0;

	std::list<uint32_t> _freeThreadIDList;
	std::map<uint32_t, TaskThread*> _liveThreads;

	std::map<std::string, uint32_t> _threadIDByName;

	Task* _rootNode = nullptr;

	TaskThread _asyncTaskThread;
	uint32_t _asyncTaskThreadID;

	uint32_t getFreeTaskThread();

	ResourceCreator& _resCreator;
public:
	TaskTree(ResourceCreator& resCreator);
	~TaskTree();

	void walk();

	void addTask(Task* task);
	void removeTask(Task* task);

	std::shared_ptr<TaskHandle> createPeriodicTask(std::function<void()> executionFunc,
		std::function<void(std::unique_ptr<TaskCompletionStatus>)> completionFunc,
		std::string threadName, bool isCyclic, int executionPeriod, bool freeOnComplete);

	std::shared_ptr<TaskHandle> createThreadedTask(std::function<void()> executionFunc,
		std::function<void(std::unique_ptr<TaskCompletionStatus>)> completionFunc, 
		std::string threadName, bool isCyclic, int timePriority, bool freeOnComplete);
};

