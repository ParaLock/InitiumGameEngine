#include "../include/LightComponent.h"



LightComponent::LightComponent(Light* light, int index, IEntity* entity)
{
	setType(COMPONENT_TYPE::LIGHT_COMPONENT);

	_index = index;

	_light = light;

	_parent = entity;

	_parent->getRenderObject()->addLight(_light, _index);
}


LightComponent::~LightComponent()
{
}

void LightComponent::update(float delta)
{
	_light->setPosition(_parent->getTransform()->getPos());

	Vector3f pos = _parent->getTransform()->getPos();

	_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::LIGHT_RENDER_NODE, _index)->
		setPerNodeParam_Transform(_parent->getTransform());

	_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::LIGHT_RENDER_NODE, _index)->
		setPerNodeParam_isVisible(true);
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}
