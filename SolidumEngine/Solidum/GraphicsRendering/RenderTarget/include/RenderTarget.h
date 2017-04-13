#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"
#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../../GraphicsRendering/Viewport/include/Viewport.h"

#include "../../ActiveGraphicsAPI.h"

class RenderTarget : public IResource
{
protected:

	Viewport _viewPort;

	int _mipLevel;
	int _aaSamples;
	TEX_FORMAT _texFormat;

public:
	RenderTarget();
	~RenderTarget();

	struct InitData : public IResourceBuilder {
		int _mipLevel;
		int _aaSamples;
		TEX_FORMAT _texFormat;

		int _height;
		int _width;

		InitData(int mipLevel, int aaSamples, TEX_FORMAT texFormat, int height, int width) {
			_mipLevel = mipLevel;
			_aaSamples = aaSamples;
			_texFormat = texFormat;
			_height = height;
			_width = width;
		}
	};

	Viewport& getViewport() { return _viewPort; }

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	virtual void Clear(float R, float G, float B, float A) = 0;
};

