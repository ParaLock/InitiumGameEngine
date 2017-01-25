#include "../include/EventHub.h"



EventHub::EventHub()
{
	_listeners = new std::list<IEventListener*>;
}


EventHub::~EventHub()
{
	delete _listeners;
}

void EventHub::subscribeListener(IEventListener * listener)
{
	_listeners->push_back(listener);
}

void EventHub::publishEvent(IEvent * evt)
{
	for (auto itr = _listeners->begin(); itr != _listeners->end(); itr++) {
			
		IEventListener* sub = *itr;
	
		sub->onEvent(evt);
	}
}
