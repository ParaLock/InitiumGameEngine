#include "../include/EntityRenderObject.h"



EntityRenderObject::EntityRenderObject()
{
}


EntityRenderObject::~EntityRenderObject()
{
}

void EntityRenderObject::addLight(ILight * light, int lightIndex)
{
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	LightRenderNode* newNode = new LightRenderNode((Light*)light, tree->getUniqueNodeID());

	if (_renderResources.find(RENDER_NODE_TYPE::LIGHT_RENDER_NODE) == _renderResources.end()) {
		_renderResources.insert({ RENDER_NODE_TYPE::LIGHT_RENDER_NODE, new std::map<int, RenderNode*> });
	}

	_renderResources[RENDER_NODE_TYPE::LIGHT_RENDER_NODE]->insert({lightIndex, newNode});
	
	tree->addNode(newNode, newNode->getID());
}

void EntityRenderObject::addTexture(Texture * tex, int targetMeshIndex)
{
	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) != _renderResources.end())
	{
		MeshRenderNode* meshNode = (MeshRenderNode*)_renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->operator[](targetMeshIndex);
		meshNode->setTexture(tex);
	}
}

void EntityRenderObject::addMaterial(Material * mat, int targetMeshIndex)
{
	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) != _renderResources.end())
	{
		MeshRenderNode* meshNode = (MeshRenderNode*)_renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->operator[](targetMeshIndex);
		meshNode->setMaterial(mat);
	}
}

void EntityRenderObject::addStaticGeometry(mesh * model, int meshIndex)
{
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	MeshRenderNode* newNode = new MeshRenderNode(model, tree->getUniqueNodeID());

	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) == _renderResources.end()) {
		_renderResources.insert({ RENDER_NODE_TYPE::MESH_RENDER_NODE, new std::map<int, RenderNode*> });
	}

	_renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->insert({ meshIndex, newNode });

	tree->addNode(newNode, newNode->getID());
}

void EntityRenderObject::addAnimatedMesh(mesh * animation, int animationMeshIndex)
{
}

void EntityRenderObject::addGenericRenderNode(RenderNode * renderNode, RENDER_NODE_TYPE type, int genericNodeIndex)
{
	if (_renderResources.find(type) == _renderResources.end()) {
		_renderResources.insert({ type, new std::map<int, RenderNode*> });
	}

	_renderResources[type]->insert({ genericNodeIndex, renderNode });
	
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();
	
	tree->addNode(renderNode, renderNode->getID());
}

void EntityRenderObject::updateRenderNode(RENDER_NODE_TYPE nodeType, int index, RenderParams & params)
{
	if (_renderResources.find(nodeType) != _renderResources.end()) {

		GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeLocalRenderParams(
			params.getAllLocalParams(), _renderResources[nodeType]->operator[](index)->getID());
	}
}
