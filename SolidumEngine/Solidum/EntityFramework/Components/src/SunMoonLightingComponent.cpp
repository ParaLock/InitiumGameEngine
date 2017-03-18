#include "../include/SunMoonLightingComponent.h"



SunMoonLightingComponent::SunMoonLightingComponent(Light* sun, Light* moon, float speed)
{
	_sun = sun;
	_moon = moon;

	setType(COMPONENT_TYPE::SUN_COMPONENT);

	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	_renderNodeID[0] = tree->getUniqueNodeID();
	_renderNodeID[1] = tree->getUniqueNodeID();

	tree->addNode(new LightRenderNode(_sun), _renderNodeID[0]);
	tree->addNode(new LightRenderNode(_sun), _renderNodeID[1]);

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
