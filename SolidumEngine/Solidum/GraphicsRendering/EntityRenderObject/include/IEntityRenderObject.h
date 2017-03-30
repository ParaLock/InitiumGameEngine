#pragma once
#include "../../../sysInclude.h"

class ILight;
class Texture;
class Material;
class mesh;
class RenderNode;
class RenderParams;

class IEntityRenderObject
{
public:
	IEntityRenderObject() {};
	~IEntityRenderObject() {};

	virtual void addLight(ILight* light, int lightIndex) = 0;
	virtual void addTexture(Texture* tex, int targetMeshIndex) = 0;
	virtual void addMaterial(Material* mat, int targetMeshIndex) = 0;
	virtual void addStaticGeometry(mesh* model, int meshIndex) = 0;
	virtual void addAnimatedMesh(mesh* animation, int animationMeshIndex) = 0;

	virtual void addGenericRenderNode(RenderNode* renderNode, RENDER_NODE_TYPE type, int genericNodeIndex) = 0;

	virtual void updateRenderNode(RENDER_NODE_TYPE nodetype, int index, RenderParams& params) = 0;
};

