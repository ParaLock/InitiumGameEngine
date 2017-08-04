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

	std::unordered_map<std::type_index, std::vector<IComponent*>> _components;

	Transform* _transform;

	IEntity* _parent = nullptr;

	World* _parentWorld;

public:
	Entity();
	~Entity();

	template<typename T>
	T* getComponent(int index) {
		
		auto& itr = _components.find(std::type_index(typeid(T)));

		if (itr != _components.end()) {

			auto& compList = itr->second;

			if (index <= compList.size()) {

				return (T*)compList.at(index);

			}

		}

		return nullptr;
	}

	template<typename T>
	std::list<T*>& getComponents() {

		auto& itr = _components.find(std::type_index(typeid(T)));

		if (itr != _components.end()) {

			auto& compList = itr->second;

			return *compList;
		}

		return std::list<T*>();

	}

	void setWorld(World* world) { _parentWorld = world; }

	template<typename T>
	void addComponent(IComponent* comp) {

		auto& itr = _components.find(std::type_index(typeid(T)));

		if (itr != _components.end()) {

			auto& compList = itr->second;

			compList.push_back(comp);
		}
		else {

			_components.insert({ std::type_index(typeid(T)), std::vector<IComponent*>{comp} });

		}

	}

	void addChild(IEntity* entity);

	IEntityRenderObject* getRenderObject() { return _renderObject; }

	void setParent(IEntity* parent);
	IEntity* getParent() { return _parent; }
	
	World* getWorld() { return _parentWorld; }

	Transform* getTransform() { return _transform; }

	void update(float delta, RenderDataGroup* collection);
};

