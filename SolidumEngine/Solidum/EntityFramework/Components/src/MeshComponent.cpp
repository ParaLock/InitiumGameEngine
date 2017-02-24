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
	int nodeCount = 0;

	LocalRenderingParams params;

	params._transform = _parent->getTransform();

	for each (uint64_t nodeid in _renderNodes) {

		if (nodeCount > 0) {
			params._depthTestEnabled = false;
		}

		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeVisibility(true, nodeid);
		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeLocalRenderParams(params, nodeid);

		nodeCount++;
	}

	params._depthTestEnabled = true;
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
