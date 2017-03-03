#pragma once
#include "../../../sysInclude.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../Components/include/IComponent.h"

#include "../../../WorldSimulation/include/World.h"

#include "IEntity.h"

class Entity : public IEntity
{
private:
	World* _world;

	std::list<IEntity*>* _children;

	std::map<COMPONENT_TYPE, IComponent*>* _components;

	Transform* _transform;

	IEntity* _parent = nullptr;

public:
	Entity(World* world);
	~Entity();

	void addComponent(IComponent* comp);
	void addChild(IEntity* entity);

	IComponent* getComponentByType(COMPONENT_TYPE type);

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }
	
	World* getWorld() { return _world; }

	Transform* getTransform() { return _transform; }

	void update();
};

