#include "../include/LightComponent.h"



LightComponent::LightComponent(Light* light)
{
	setType(COMPONENT_TYPE::LIGHT_COMPONENT);

	_parentTransformDirty = true;

	_light = light;

	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	uint64_t newNodeid = tree->getUniqueNodeID();

	_renderNodes.push_back(newNodeid);

	tree->addNode(new LightRenderNode(_light), newNodeid);
}


LightComponent::~LightComponent()
{
	for each (uint64_t nodeid in _renderNodes)
		GraphicsCore::getInstance()->getRenderNodeTree()->removeNode(nodeid);
}

void LightComponent::update()
{
	if (_parentTransformDirty) {

		_parentTransformDirty = false; 
		_parent->getTransform()->setPos(_light->getPosition());
	}

	_light->setPosition(_parent->getTransform()->getPos());

	LocalRenderingParams params;

	params._transform = _parent->getTransform();

	for each (uint64_t nodeid in _renderNodes) {

		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeVisibility(true, nodeid);
		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeLocalRenderParams(params, nodeid);
	}
}

void LightComponent::onEvent(EVENT_PTR evt)
{
}
