#include "../include/SunMoonLightingComponent.h"



SunMoonLightingComponent::SunMoonLightingComponent(Light* sun, Light* moon, float speed, IEntity* entity)
{
	_sun = sun;
	_moon = moon;

	setType(COMPONENT_TYPE::SUN_COMPONENT);

	_speed = speed;

	_parent = entity;
}


SunMoonLightingComponent::~SunMoonLightingComponent()
{
}

void SunMoonLightingComponent::update(float delta)
{
}
