#pragma once
class IComponent;
class Transform;

class IEntity
{
public:
	IEntity();
	~IEntity();

	virtual void addComponent(IComponent* comp) = 0;
	virtual void addChild(IEntity* entity) = 0;

	virtual void setParent(IEntity* parent) = 0;
	virtual IEntity* getParent() = 0;

	virtual Transform* getTransform() = 0;

	virtual void update() = 0;
};

