#pragma once
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../Entity/include/IEntity.h"

class IComponent : public IEventListener
{
private:
protected:
public:
	IComponent();
	~IComponent();

	virtual COMPONENT_TYPE getType() = 0;

	virtual void update(float delta) = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	virtual void setParent(IEntity* parent) = 0;
	virtual IEntity* getParent() = 0;
};

