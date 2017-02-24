#pragma once
#include "../../sysInclude.h"
#include "IEventListener.h"

class EventHub
{
private:
	std::list<IEventListener*> *_listeners;
public:
	EventHub();
	~EventHub();

	void subscribeListener(IEventListener* listener);

	void publishEvent(EVENT_PTR evt);
};

