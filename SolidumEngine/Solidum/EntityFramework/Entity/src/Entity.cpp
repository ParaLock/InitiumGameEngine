#include "../include/Entity.h"



Entity::Entity(World* world)
{
	_transform = new Transform;
	_components = new std::map<COMPONENT_TYPE, IComponent*>;
	_children = new std::list<IEntity*>;

	_world = world;
}


Entity::~Entity()
{
	delete _transform;
	delete _components;
	delete _children;
}

void Entity::addComponent(IComponent * comp)
{
	comp->setParent(this);

	_components->operator[](comp->getType()) = comp;
}

void Entity::addChild(IEntity * entity)
{
	entity->setParent(this);

	_children->push_back(entity);
}

IComponent * Entity::getComponentByType(COMPONENT_TYPE type)
{
	return _components->at(type);
}

void Entity::update()
{
	if (_parent != nullptr) 
		_transform->setPos(_parent->getTransform()->getPos());

	for (auto itr = _components->begin(); itr != _components->end(); itr++) {
		
		IComponent* comp = itr->second;
		
		comp->update();
	}

	for (auto itr = _children->begin(); itr != _children->end(); itr++) {

		IEntity* child = *itr;

		child->update();
	}

}
