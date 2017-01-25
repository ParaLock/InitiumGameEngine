#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"
#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../ActiveGraphicsAPI.h"

class RenderTargetBuilder : public IResourceBuilder {
public:
	int _mipLevel;
	int _aaSamples;
	TEX_FORMAT _texFormat;

	RenderTargetBuilder(int mipLevel, int aaSamples, TEX_FORMAT texFormat) {
		_mipLevel = mipLevel;
		_aaSamples = aaSamples;
		_texFormat = texFormat;
	}
};

class RenderTarget : public IResource
{
protected:

	int _mipLevel;
	int _aaSamples;
	int _texFormat;

public:
	RenderTarget();
	~RenderTarget();

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);

	virtual void Clear(float R, float G, float B, float A);
};

