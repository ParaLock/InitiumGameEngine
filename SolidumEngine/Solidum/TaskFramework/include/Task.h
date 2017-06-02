#pragma once
#include "../../sysInclude.h"
#include "../../ResourceFramework/include/IResource.h"


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

class Task : public IResource
{
private:
	void load(std::shared_ptr<IResourceBuilder> builder) {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::shared_ptr<TaskHandle> _handle;

	TASK_TYPE _type;


protected:
	Task* _child = nullptr;
	Task* _parent = nullptr;

	int _priority = 0;

	bool _freeOnComplete;

	bool _cyclicTask = false;
	bool _processed = false;

	void setType(TASK_TYPE type) { _type = type; };

	std::function<void()> _executionCallback;
	std::function<void(std::unique_ptr<TaskCompletionStatus>)> _completionCallback;
public:
	Task();
	~Task();

	bool _isComplete = false;

	void unload();

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

	TASK_TYPE getType() { return _type; }
};

