#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat)
{
	_renderNodes = mat->generateClientRenderNodes(mesh, tex);
}

MeshComponent::~MeshComponent()
{
	for each (uint64_t nodeid in _renderNodes)
		GraphicsCore::getInstance()->getRenderNodeTree()->removeNode(nodeid);
}

void MeshComponent::update()
{
	LocalRenderingParams params;

	params._transform = _parent->getTransform();

	for each (uint64_t nodeid in _renderNodes) {

		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeVisibility(true, nodeid);
		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeLocalRenderParams(params, nodeid);
	}
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
