#pragma once
#include "../../sysInclude.h"

#include "IEventListener.h"

class IEventPublisher
{
private:
	//std::list<IEventListener*> *_subscriberList;
public:
	IEventPublisher();
	~IEventPublisher();

	//void subscribe(IEventListener* listener);
	//void unsubscribe(IEventListener* listener);

	//void publishEvent(IEvent* evt);
};

