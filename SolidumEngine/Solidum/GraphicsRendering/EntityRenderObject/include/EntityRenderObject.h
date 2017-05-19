#pragma once
#include "../../../sysInclude.h"

#include "../../RenderNode/include/RenderNode.h"
#include "../../RenderNode/include/LightRenderNode.h"
#include "../../RenderNode/include/MeshRenderNode.h"

#include "../../RenderNodeTree/include/RenderNodeTree.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../RenderNode/include/RenderNodePool.h"

#include "IEntityRenderObject.h"

typedef std::map<int, uint64_t>* ENTITY_INDEXED_RENDER_RESOURCE;

class EntityRenderObject : public IEntityRenderObject
{
private:
	std::map<RENDER_NODE_TYPE, ENTITY_INDEXED_RENDER_RESOURCE> _renderResources;
public:
	EntityRenderObject();
	~EntityRenderObject();

	void addLight(ILight* light, int lightIndex);
	void addTexture(Texture* tex, int targetMeshIndex);
	void addMaterial(Material* mat, int targetMeshIndex);
	void addStaticGeometry(mesh* model, int meshIndex);
	void addAnimatedMesh(mesh* animation, int animationMeshIndex);

	void addGenericRenderNode(RenderNode* renderNode, int genericNodeIndex);

	RenderParams* updateRenderNodeParams(RENDER_NODE_TYPE objtype, int index);
};

