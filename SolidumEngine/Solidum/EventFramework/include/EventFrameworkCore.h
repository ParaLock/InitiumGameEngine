#pragma once
#include "../../sysInclude.h"

#include "EventHub.h"

class EventFrameworkCore
{
private:
	std::map<std::string, EventHub*> *_globalEventHubs;
public:
	EventFrameworkCore();
	~EventFrameworkCore();

	void registerGlobalEventHub(EventHub* evtHub, std::string name);
	EventHub* getGlobalEventHub(std::string name);

	static EventFrameworkCore* singletonInstance;
	static EventFrameworkCore* getInstance();
};

