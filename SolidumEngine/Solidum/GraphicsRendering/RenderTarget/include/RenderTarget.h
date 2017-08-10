#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../GraphicsRendering/Viewport/include/Viewport.h"

#include "../../DepthStencil/include/DepthStencil.h"

#include "../include/RenderTargetFactory.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

class RenderTarget;
class dxRenderTarget;

class ResourcePool;

class RenderTarget : public Resource<RenderTarget, RenderTargetFactory, ResourcePool>
{
public:
	RenderTarget();
	~RenderTarget();

	struct InitData : public ResourceInitParams {
		TEX_FORMAT _texFormat;

		int _height;
		int _width;

		bool _createDepthStencil;

		InitData() {}

		

		InitData(TEX_FORMAT texFormat, int height, int width) {
			_texFormat = texFormat;
			_height = height;
			_width = width;
		}
	};

	Viewport& getViewport() { return _viewPort; }
	void setViewport(Viewport& view) { _viewPort = view; }

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void Clear(float R, float G, float B, float A) = 0;

protected:
	Viewport _viewPort;

	int _mipLevel;
	int _aaSamples;
	TEX_FORMAT _texFormat;
};
