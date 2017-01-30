#pragma once
#include "../../../sysInclude.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../Components/include/IComponent.h"

#include "IEntity.h"

class Entity : public IEntity
{
private:
	std::list<IEntity*>* _children;
	std::list<IComponent*>* _components;

	Transform* _transform;

	IEntity* _parent = nullptr;

public:
	Entity();
	~Entity();

	void addComponent(IComponent* comp);
	void addChild(IEntity* entity);

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }
	
	Transform* getTransform() { return _transform; }

	void update();
};

