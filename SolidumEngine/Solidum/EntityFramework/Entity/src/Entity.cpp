#include "../include/Entity.h"



Entity::Entity()
{
	_renderObject = new EntityRenderObject();

	_transform = new Transform;
	_components = new std::map<COMPONENT_TYPE, std::list<IComponent*>*>;
	_children = new std::list<IEntity*>;
}


Entity::~Entity()
{
	delete _transform;
	delete _components;
	delete _children;
}

void Entity::addComponent(IComponent * comp)
{
	if (_components->operator[](comp->getType()) == nullptr) 
		_components->operator[](comp->getType()) = new std::list<IComponent*>;

	_components->operator[](comp->getType())->push_back(comp);
}

void Entity::addChild(IEntity * entity)
{
	entity->setParent(this);

	_children->push_back(entity);
}

std::list<IComponent*> * Entity::getComponentsByTypeAndIndex(COMPONENT_TYPE type, int index)
{
	return _components->at(type);
}

void Entity::update(float delta)
{
	if (_parent != nullptr) 
		_transform->setPos(_parent->getTransform()->getPos());

	for (auto itr = _components->begin(); itr != _components->end(); itr++) {
		
		for (auto compItr = _components->at(itr->first)->begin();
			 compItr != _components->at(itr->first)->end(); compItr++) {

			IComponent* comp = *compItr;

			comp->update(delta);
		}
	}

	for (auto itr = _children->begin(); itr != _children->end(); itr++) {

		IEntity* child = *itr;

		child->update(delta);
	}

	
}
