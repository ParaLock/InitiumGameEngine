#pragma once
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../Entity/include/IEntity.h"

enum COMPONENT_TYPE {
	MOVE_COMPONENT,
	LIGHT_COMPONENT,
	MESH_COMPONENT
};

class IComponent : public IEventListener
{
private:
protected:
public:
	IComponent();
	~IComponent();

	virtual COMPONENT_TYPE getType() = 0;

	virtual void update() = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	virtual void setParent(IEntity* parent) = 0;
	virtual IEntity* getParent() = 0;
};

