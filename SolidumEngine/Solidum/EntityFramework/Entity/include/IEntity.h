#pragma once
#include "../../../sysInclude.h"

class IComponent;
class Transform;
class World;

class IEntityRenderObject;
class RenderDataGroup;

class IEntity
{
public:
	IEntity();
	~IEntity();

	virtual void setWorld(World* world) = 0;

	virtual void addChild(IEntity* entity) = 0;

	virtual IEntityRenderObject* getRenderObject() = 0;

	virtual void setParent(IEntity* parent) = 0;
	virtual IEntity* getParent() = 0;

	virtual Transform* getTransform() = 0;

	virtual World* getWorld() = 0;

	virtual void update(float delta, RenderDataGroup* collection) = 0;
};

