#include "../include/LightComponent.h"



LightComponent::LightComponent(Light* light, int index)
{
	setType(COMPONENT_TYPE::LIGHT_COMPONENT);

	_index = index;

	_parentTransformDirty = true;

	_light = light;
}


LightComponent::~LightComponent()
{
}

void LightComponent::init()
{
	if(_parent != nullptr)
		_parent->getRenderObject()->addLight(_light, _index);
}

void LightComponent::update(float delta)
{
	if (_parentTransformDirty && _parent != nullptr) {

		_parentTransformDirty = false; 
		_parent->getTransform()->setPos(_light->getPosition());
	}

	_light->setPosition(_parent->getTransform()->getPos());
	
	if (_parent != nullptr) {

		_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::LIGHT_RENDER_NODE, _index)->
			setPerNodeParam_Transform(_parent->getTransform());

		_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::LIGHT_RENDER_NODE, _index)->
			setPerNodeParam_isVisible(true);
	}
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}
