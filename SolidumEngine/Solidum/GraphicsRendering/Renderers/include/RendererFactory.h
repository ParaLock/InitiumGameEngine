#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/ResourceFactory.h"

#include "Renderer.h"

#include "GeometryDeferredRenderer.h"
#include "GeometryForwardRenderer.h"
#include "LightRenderer.h"
#include "ParticleRenderer.h"
#include "ShadowMapRenderer.h"
#include "SkyRenderer.h"

class RendererFactory : public ResourceFactory<Renderer, RENDERER_TYPE>
{
public:
	RendererFactory();
	~RendererFactory();

	Renderer* createObject(RENDERER_TYPE type);
};

