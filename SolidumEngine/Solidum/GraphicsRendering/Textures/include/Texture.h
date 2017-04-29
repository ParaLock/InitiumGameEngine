#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

class Texture : public IResource
{
protected:
	int _width = 0;
	int _height = 0;
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

	int getHeight() { return _height; }
	int getWidth() { return _width; }

	virtual void loadImage(LPCWSTR filename);
};

