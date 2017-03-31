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

	LightRenderNode* newNode = new LightRenderNode(tree->getUniqueNodeID());

	tree->addNode(newNode, newNode->getID());

	if (_renderResources.find(RENDER_NODE_TYPE::LIGHT_RENDER_NODE) == _renderResources.end()) {
		_renderResources.insert({ RENDER_NODE_TYPE::LIGHT_RENDER_NODE, new std::map<int, uint64_t> });
	}

	_renderResources[RENDER_NODE_TYPE::LIGHT_RENDER_NODE]->insert({lightIndex, newNode->getID()});
	
	updateRenderNodeParams(RENDER_NODE_TYPE::LIGHT_RENDER_NODE, lightIndex)->
		setPerNodeParam_Light((Light*)light);
}

void EntityRenderObject::addTexture(Texture * tex, int targetMeshIndex)
{
	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) != _renderResources.end())
	{
		uint64_t nodeID = _renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->operator[](targetMeshIndex);

		updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, targetMeshIndex)->
			setPerNodeParam_MeshTexture(tex);
	}
}

void EntityRenderObject::addMaterial(Material * mat, int targetMeshIndex)
{
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) != _renderResources.end())
	{
		uint64_t nodeID = _renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->operator[](targetMeshIndex);

		updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, targetMeshIndex)->
			setPerNodeParam_MeshMaterial(mat);
	}
}

void EntityRenderObject::addStaticGeometry(mesh * model, int meshIndex)
{
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();

	MeshRenderNode* newNode = new MeshRenderNode(tree->getUniqueNodeID());

	tree->addNode(newNode, newNode->getID());

	if (_renderResources.find(RENDER_NODE_TYPE::MESH_RENDER_NODE) == _renderResources.end()) {
		_renderResources.insert({ RENDER_NODE_TYPE::MESH_RENDER_NODE, new std::map<int, uint64_t> });
	}

	_renderResources[RENDER_NODE_TYPE::MESH_RENDER_NODE]->insert({ meshIndex, newNode->getID() });

	updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, meshIndex)->
		setPerNodeParam_Mesh(model);
}

void EntityRenderObject::addAnimatedMesh(mesh * animation, int animationMeshIndex)
{
}

void EntityRenderObject::addGenericRenderNode(RenderNode * renderNode, RENDER_NODE_TYPE type, int genericNodeIndex)
{
	if (_renderResources.find(type) == _renderResources.end()) {
		_renderResources.insert({ type, new std::map<int, uint64_t> });
	}

	_renderResources[type]->insert({ genericNodeIndex, renderNode->getID() });
	
	RenderNodeTree* tree = GraphicsCore::getInstance()->getRenderNodeTree();
	
	tree->addNode(renderNode, renderNode->getID());
}

RenderParams* EntityRenderObject::updateRenderNodeParams(RENDER_NODE_TYPE nodeType, int index)
{
	if (_renderResources.find(nodeType) != _renderResources.end()) {

		return GraphicsCore::getInstance()->getRenderNodeTree()->
			getRenderNodeParams(_renderResources[nodeType]->operator[](index));
	}

	return nullptr;
}
