#include "../include/EventFrameworkCore.h"

EventFrameworkCore* EventFrameworkCore::singletonInstance = nullptr;

EventFrameworkCore * EventFrameworkCore::getInstance()
{
	return singletonInstance;
}


EventFrameworkCore::EventFrameworkCore()
{
	_globalEventHubs = new std::map<std::string, EventHub*>;

	if(singletonInstance == nullptr)
	singletonInstance = this;
}


EventFrameworkCore::~EventFrameworkCore()
{
	delete _globalEventHubs;
}

void EventFrameworkCore::registerGlobalEventHub(EventHub * evtHub, std::string name)
{
	_globalEventHubs->insert({name, evtHub});
}

EventHub * EventFrameworkCore::getGlobalEventHub(std::string name)
{
	auto itr = _globalEventHubs->find(name);

	if (itr != _globalEventHubs->end()) {
		return _globalEventHubs->at(name);
	}
	else {
		std::cout << "EVENT FRAMEWORK: Could not find event HUB: " << name;
	}

	return nullptr;
}

