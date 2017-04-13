#pragma once
#include "../../../sysInclude.h"

#include "RenderNode.h"
#include "LightRenderNode.h"
#include "MeshRenderNode.h"
#include "ShadowGenRenderNode.h"
#include "SkyBoxRenderNode.h"

#include "../../../ResourceFramework/include/ResourceFactory.h"

class RenderNodeFactory : public ResourceFactory<RenderNode, RENDER_NODE_TYPE>
{
public:
	RenderNodeFactory();
	~RenderNodeFactory();

	RenderNode* createObject(RENDER_NODE_TYPE type);
};

