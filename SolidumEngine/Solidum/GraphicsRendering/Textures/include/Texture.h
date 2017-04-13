#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

class Texture : public IResource
{
public:
	Texture();
	~Texture();

	struct InitData : public IResourceBuilder {
		LPCWSTR _filename;

		InitData(LPCWSTR filename) {
			_filename = filename;
		}
	};

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	virtual void loadImage(LPCWSTR filename);
};

