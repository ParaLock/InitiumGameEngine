#include "../include/SunMoonLightingComponent.h"



SunMoonLightingComponent::SunMoonLightingComponent(Light* sun, Light* moon, float speed, IEntity* entity)
{
	_sun = sun;
	_moon = moon;

	_speed = speed;

	_parent = entity;
}


SunMoonLightingComponent::~SunMoonLightingComponent()
{
}

void SunMoonLightingComponent::update(float delta)
{
}
