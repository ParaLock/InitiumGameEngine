#include "../include/GraphicsComponent.h"


GraphicsComponent::GraphicsComponent(std::string meshID, std::string texID, 
	std::string matID, std::string shaderID, std::string lightID, Transform* transform)
{
	_meshID = meshID;
	_texID = texID;
	_matID = matID;
	_shaderID = shaderID;
	_lightID = lightID;
	_transform = transform;
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::update()
{
	RenderEvent* EntityGraphicsUpdate = new RenderEvent();

	EntityGraphicsUpdate->setMaterialID(_matID);
	EntityGraphicsUpdate->setMeshID(_meshID);
	EntityGraphicsUpdate->setTextureID(_texID);
	EntityGraphicsUpdate->setShaderID(_shaderID);
	EntityGraphicsUpdate->setLightID(_lightID);

	EntityGraphicsUpdate->setTransform(_transform);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(EntityGraphicsUpdate);
}
