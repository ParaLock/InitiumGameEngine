#include "../include/RenderNodeFactory.h"



RenderNodeFactory::RenderNodeFactory()
{
}


RenderNodeFactory::~RenderNodeFactory()
{
}

RenderNode * RenderNodeFactory::createObject(RENDER_NODE_TYPE type)
{
	RenderNode* renderNode;

	switch (type)
	{
	case RENDER_NODE_TYPE::LIGHT_RENDER_NODE:
		renderNode = new LightRenderNode();
		break;
	case RENDER_NODE_TYPE::MESH_RENDER_NODE:
		renderNode = new MeshRenderNode();
		break;
	case RENDER_NODE_TYPE::SKYBOX_WEATHER_RENDER_NODE:
		renderNode = new SkyBoxRenderNode();
		break;
	case RENDER_NODE_TYPE::SHADOW_GEN_RENDER_NODE:
		renderNode = new ShadowGenRenderNode();
		break;
	case RENDER_NODE_TYPE::POST_FX_RENDER_NODE:
		break;
	default:
		renderNode = nullptr;
		break;
	}


	int debugPoint = -1;

	return renderNode;
}
