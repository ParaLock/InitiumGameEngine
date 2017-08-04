#pragma once
#include "../../sysInclude.h"
#include "../../ResourceFramework/include/Resource.h"

#include "../../ResourceFramework/include/GenericFactory.h"

struct TaskCompletionStatus {

	TaskCompletionStatus(TASK_COMPLETION_STATUS stat) {
		status = stat;
	}

	TASK_COMPLETION_STATUS status;
};

class TaskHandle {
private:
public:

	bool _taskFreed = false;
	bool _taskComplete = false;
};

class ResourcePool;

class Task : public Resource<Task, GenericFactory, ResourcePool>
{
private:
	void load() {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::shared_ptr<TaskHandle> _handle;

	std::function<void(Task*)> _parentThreadEnqueue;

protected:
	Task* _child = nullptr;
	Task* _parent = nullptr;

	int _priority = 0;

	bool _freeOnComplete;

	bool _cyclicTask = false;
	bool _processed = false;

	std::function<void()> _executionCallback;
	std::function<void(std::unique_ptr<TaskCompletionStatus>)> _completionCallback;
public:
	Task();
	~Task();

	struct InitData : public ResourceInitParams {

		

		InitData() {}
	};

	bool _isComplete = false;

	void unload();

	void setEnQueueFunction(std::function<void(Task*)> func) { _parentThreadEnqueue = func; };

	void touch();
	void execute();

	void start() { _isComplete = false; }
	void stop();

	void setCyclicState(bool isCyclic) { _cyclicTask = isCyclic; }
	void setPriority(int priority);

	void setHandle(std::shared_ptr<TaskHandle> handle) { _handle = handle; }

	void setFreeOnComplete(bool status) { _freeOnComplete = status; };

	void setExecutionCallback(std::function<void()> func);
	void setCompletionCallback(std::function<void(std::unique_ptr<TaskCompletionStatus>)> func);

	void setChild(Task* child) { 

		_child = child; 
	};
	void setParent(Task* parent) { 

		_parent = parent; 
	}

	bool isComplete() { return _isComplete; }
	bool isCyclic() { return _cyclicTask; }
	bool isFreeOnComplete() { return _freeOnComplete; }

	std::shared_ptr<TaskHandle> getHandle() { return _handle; };

	int getPriority();

	Task* getChild() { return _child; }
	Task* getParent() { return _parent; }

protected:
};

