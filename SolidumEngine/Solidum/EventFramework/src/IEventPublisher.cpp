#include "../include/IEventPublisher.h"



IEventPublisher::IEventPublisher()
{
	//_subscriberList = new std::list<IEventListener*>;
}


IEventPublisher::~IEventPublisher()
{
	//delete _subscriberList;
}

//void IEventPublisher::subscribe(IEventListener * listener)
//{
//	_subscriberList->push_back(listener);
//}
//
//void IEventPublisher::unsubscribe(IEventListener * listener)
//{
//	for (auto itr = _subscriberList->begin(); itr != _subscriberList->end(); itr++) {
//		if (*itr == listener) {
//			
//			_subscriberList->remove(*itr);
//			
//			break;
//		}
//	}
//}
//
//void IEventPublisher::publishEvent(IEvent* evt)
//{
//	for (auto itr = _subscriberList->begin(); itr != _subscriberList->end(); itr++) {
//		
//		IEventListener* sub = *itr;
//
//		sub->onEvent(evt);
//	}
//}
