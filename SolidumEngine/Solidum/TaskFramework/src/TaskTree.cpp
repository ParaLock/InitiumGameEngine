#include "../include/TaskTree.h"

uint32_t TaskTree::getFreeTaskThread()
{
	uint32_t id;

	if (_freeThreadIDList.empty()) {
		id = getRandomNumber();

		_liveThreads.insert({id, new TaskThread()});

		return id;
	}

	id = _freeThreadIDList.front();

	_freeThreadIDList.pop_front();

	return id;
}

TaskTree::TaskTree()
{
	_taskPool.setFactory(&_taskFactory);

	_asyncTaskThreadID = getRandomNumber();
}


TaskTree::~TaskTree()
{
}

void TaskTree::walk()
{
	Task* node = _rootNode;

	if (node == nullptr)
		return;

	while (node->getChild() != nullptr) {
		node = node->getChild();

		node->touch();

		if (node->_isComplete) {
			removeTask(node);
		}
	}
}

void TaskTree::addTask(Task * task)
{

	Task* temp = _rootNode;

	if (_rootNode == nullptr) {
		_rootNode = task;

		return;
	}

	while (temp->getChild() != nullptr) {
		temp = temp->getChild();
	}

	temp->setChild(task);
}

void TaskTree::removeTask(Task * node)
{
	//Is root node
	if (node->getParent() == nullptr) {
		//Root has child
		if (node->getChild() != nullptr) {
			node->getChild()->setParent(nullptr);

			_rootNode = node->getChild();

			node->setChild(nullptr);
			node->setParent(nullptr);

			_taskPool.releaseResource(node);
		}
		//Root does not have child
		else {
			_taskPool.releaseResource(node);

			node->setChild(nullptr);
			node->setParent(nullptr);

			_rootNode = nullptr;
		}
	}
	//Is child of root
	else {
		//Has child
		if (node->getChild() != nullptr) {

			node->getChild()->setParent(node->getParent());
			node->getParent()->setChild(node->getChild());

			node->setChild(nullptr);
			node->setParent(nullptr);

		}
		//Does not have child
		else {
			node->getParent()->setChild(nullptr);

			node->setChild(nullptr);
			node->setParent(nullptr);

			_taskPool.releaseResource(node);
		}
	}
}

std::shared_ptr<TaskHandle> TaskTree::createPeriodicTask(
	std::function<void()> executionFunc,
	std::function<void(std::unique_ptr<TaskCompletionStatus>)> completionFunc, 
	std::string threadName, bool isCyclic, int executionPeriod, bool freeOnComplete)
{
	return std::shared_ptr<TaskHandle>();
}

std::shared_ptr<TaskHandle> TaskTree::createThreadedTask(
	std::function<void()> executionFunc, 
	std::function<void(std::unique_ptr<TaskCompletionStatus>)> completionFunc, 
	std::string threadName, bool isCyclic, int timePriority, bool freeOnComplete)
{

	if (_threadIDByName.find(threadName) == _threadIDByName.end()) {
		_threadIDByName.insert({threadName, getFreeTaskThread()});
	}

	Task* newTask = _taskPool.getResource(TASK_TYPE::NORMAL_TASK);

	TaskThread* taskThread = _liveThreads.at(_threadIDByName.at(threadName));

	newTask->setCompletionCallback(completionFunc);
	newTask->setExecutionCallback(executionFunc);

	newTask->setPriority(timePriority);

	newTask->setFreeOnComplete(freeOnComplete);

	newTask->setCyclicState(isCyclic);

	newTask->start();

	addTask(newTask);

	if (!taskThread->isRunning()) {

		taskThread->start();
	}

	std::shared_ptr<TaskHandle> handle = std::make_shared<TaskHandle>();

	newTask->setHandle(handle);

	taskThread->queueTask(newTask);

	return handle;
}
