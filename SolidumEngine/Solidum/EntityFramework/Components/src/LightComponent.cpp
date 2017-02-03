#include "../include/LightComponent.h"



LightComponent::LightComponent(ILight* light)
{
	_op.setLight(light);
	_op.setShader(light->getShader());

	_parentTransformDirty = true;
}


LightComponent::~LightComponent()
{
}

void LightComponent::update()
{
	if (_parent != nullptr) {

		if (_parentTransformDirty) {
			_parentTransformDirty = false;
			_parent->getTransform()->setPos(_op.getLight()->getPosition());
		}

		_op.getLight()->setPosition(_parent->getTransform()->getPos());
	}


	EVENT_PTR renderEvt = std::make_shared<RenderEvent>(EVENT_TYPE::RENDER_EVENT_QUEUE_OP);

	renderEvt.get()->getEvent<RenderEvent>()->setRenderOP(_op);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(renderEvt);
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}
