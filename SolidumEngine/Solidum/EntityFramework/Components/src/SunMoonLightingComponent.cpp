#include "../include/SunMoonLightingComponent.h"



SunMoonLightingComponent::SunMoonLightingComponent(Light* sun, Light* moon, float speed)
{
	_sun = sun;
	_moon = moon;

	setType(COMPONENT_TYPE::SUN_COMPONENT);

	_speed = speed;
}


SunMoonLightingComponent::~SunMoonLightingComponent()
{
}

void SunMoonLightingComponent::update(float delta)
{
	//GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeVisibility(true, _renderNodeID[0]);
	//GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeVisibility(true, _renderNodeID[1]);
}
