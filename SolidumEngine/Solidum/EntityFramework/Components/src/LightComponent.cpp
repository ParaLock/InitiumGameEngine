#include "../include/LightComponent.h"



LightComponent::LightComponent(ILight* light)
{
	RenderEvent* renderEvt = new RenderEvent(EVENT_TYPE::RENDER_EVENT_QUEUE_OP);

	_op = new RenderOP();

	_op->setLight(light);
	_op->setShader(light->getShader());

	renderEvt->setRenderOP(_op);

	_parentTransformDirty = true;

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(renderEvt);
}


LightComponent::~LightComponent()
{
}

void LightComponent::update()
{
	if (_parent != nullptr) {

		if (_parentTransformDirty) {
			_parentTransformDirty = false;
			_parent->getTransform()->setPos(_op->getLight()->getPosition());
		}

		_op->getLight()->setPosition(_parent->getTransform()->getPos());
		
	}

}

void LightComponent::onEvent(IEvent * evt)
{
}
