#pragma once
#include "../../../sysInclude.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../Components/include/IComponent.h"

#include "../../../WorldSimulation/include/World.h"

#include "../../../GraphicsRendering/EntityRenderObject/include/IEntityRenderObject.h"
#include "../../../GraphicsRendering/EntityRenderObject/include/EntityRenderObject.h"

#include "IEntity.h"

class Entity : public IEntity
{
private:
	IEntityRenderObject* _renderObject;

	std::list<IEntity*>* _children;

	std::map<COMPONENT_TYPE, std::list<IComponent*>*>* _components;

	Transform* _transform;

	IEntity* _parent = nullptr;

public:
	Entity();
	~Entity();

	void addComponent(IComponent* comp);
	void addChild(IEntity* entity);

	std::list<IComponent*>* getComponentsByTypeAndIndex(COMPONENT_TYPE type, int index);

	IEntityRenderObject* getRenderObject() { return _renderObject; }

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }
	
	Transform* getTransform() { return _transform; }

	void update(float delta);
};

