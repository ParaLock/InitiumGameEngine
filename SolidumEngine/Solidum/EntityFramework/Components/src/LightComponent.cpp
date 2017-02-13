#include "../include/LightComponent.h"



LightComponent::LightComponent(Light* light, mesh* mesh, std::string renderProcessName)
{
	_parentTransformDirty = true;

	_light = light;
	_mesh = mesh;

	_graphicsStream = new RenderDataStream();

	EVENT_PTR regEvt = std::make_shared<RenderEvent>(EVENT_TYPE::RENDER_EVENT_REGISTER_STREAM);
	
	regEvt->getEvent<RenderEvent>()->setData(_graphicsStream, renderProcessName);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(regEvt);
}


LightComponent::~LightComponent()
{
}

void LightComponent::update()
{
	if (_parent != nullptr) {

		if (_parentTransformDirty) {
			_parentTransformDirty = false;
			_parent->getTransform()->setPos(_light->getPosition());
		}

		_light->setPosition(_parent->getTransform()->getPos());
	}

	_graphicsStream->writeNext((IResource*)_light, STREAM_DATA_TYPE::LIGHT);
	_graphicsStream->writeNext((IResource*)_parent->getTransform(), STREAM_DATA_TYPE::TRANSFORM);
	_graphicsStream->writeNext((IResource*)_mesh, STREAM_DATA_TYPE::MESH);
	
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}
