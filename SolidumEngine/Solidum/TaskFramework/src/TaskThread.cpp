#include "../include/TaskThread.h"



TaskThread::TaskThread()
{
}


TaskThread::~TaskThread()
{
}

void TaskThread::start()
{
	_running = true;

	_executionThread = std::thread(&TaskThread::processPendingTasks, this);
}

void TaskThread::stop()
{
	_running = false;

	if (_executionThread.joinable()) {
		_executionThread.join();
	}
}

void TaskThread::queueTask(Task * task)
{
	_queueLock.lock();
	_workqueue.push_back(task);
	_queueLock.unlock();
}

void TaskThread::processPendingTasks()
{
	while (_running) {

		_queueLock.lock();

		auto& itr = _workqueue.begin();

		while(itr != _workqueue.end()) {
			Task* task = *itr;

			task->execute();

			if (task->_isComplete) {

				itr = _workqueue.erase(itr);

				continue;
			}

			itr++;
		}

		_queueLock.unlock();
	}
}

bool TaskThread::isRunning()
{
	return _running;
}
