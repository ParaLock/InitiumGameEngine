#include "..\include\RendererFactory.h"



RendererFactory::RendererFactory()
{
}


RendererFactory::~RendererFactory()
{
}

Renderer * RendererFactory::createObject(RENDERER_TYPE type)
{
	Renderer* newRenderer = nullptr;

	switch (type)
	{
	case RENDERER_TYPE::INVALID:
		break;
	case RENDERER_TYPE::GEOMETRY_DEFERRED_RENDERER:
		newRenderer = new GeometryDeferredRenderer();
		break;
	case RENDERER_TYPE::GEOMETRY_FORWARD_RENDERER:
		newRenderer = new GeometryForwardRenderer();
		break;
	case RENDERER_TYPE::LIGHT_RENDERER:
		newRenderer = new LightRenderer();
		break;
	case RENDERER_TYPE::MULTI_PASS_RENDERING:
		newRenderer = nullptr;
		break;
	case RENDERER_TYPE::SKY_RENDERER:
		newRenderer = new SkyRenderer();
		break;
	case RENDERER_TYPE::PARTICLE_RENDERER:
		newRenderer = new ParticleRenderer();
		break;
	case RENDERER_TYPE::SHADOW_RENDERER:
		newRenderer = new ShadowMapRenderer();
		break;
	default:
		break;
	}

	return newRenderer;
}
