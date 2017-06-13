#include "../include/LightComponent.h"



LightComponent::LightComponent(Light* light, int index, IEntity* entity)
{
	setType(COMPONENT_TYPE::LIGHT_COMPONENT);

	_index = index;

	_light = light;

	_parent = entity;

	_screenQuad = new mesh();
	_screenQuad->load(std::make_shared<mesh::InitData>(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));
	
	_parent->getRenderObject()->addLightComponent(this, _index);
}


LightComponent::~LightComponent()
{
}

void LightComponent::update(float delta)
{
	_light->setPosition(Matrix4f::getPos(_parent->getTransform()->getGlobalTransform()));
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}

std::shared_ptr<RenderDataPacket> LightComponent::createRenderData()
{
	RenderPassPacket_LightData light_data;

	_light->shadowUpdate(_parent->getWorld()->getBoundingSphere());

	light_data._lightColor = _light->getColor();
	light_data._lightDirection = _light->getDirection();
	light_data._lightPos = _light->getPosition();
	light_data._lightType = _light->getType();

	light_data._castsShadows = _light->getIsShadowCaster();
	light_data._shadowView = _light->getShadowMatrix();

	light_data._pointLightExponent = _light->getAttenuationExponent();
	light_data._pointLightLinear = _light->getAttenuationLinear();
	light_data._pointLightConstant = _light->getAttenuationConstant();

	light_data._projectionMatrix = _light->getProjectionMatrix();
	light_data._viewMatrix = _light->getViewMatrix();

	light_data._intensity = _light->getIntensity();

	light_data._pointLightRange = _light->getRange();

	light_data._indiceCount = 6;

	light_data._vertexBuff = _screenQuad->getVertexBuff();
	light_data._indexBuff = _screenQuad->getIndexBuff();

	std::shared_ptr<RenderDataPacket> _dataPtr = std::make_shared<RenderDataPacket>();

	_dataPtr->setType(RENDER_DATA_TYPE::RENDER_LIGHT_DATA);

	_dataPtr->addData<RenderPassPacket_LightData>(light_data);

	return _dataPtr;
}
