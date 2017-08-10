#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../include/TextureFactory.h"

class ResourcePool;

class Texture : public Resource<Texture, TextureFactory, ResourcePool>
{
public:
	Texture();
	~Texture();

	struct InitData : public ResourceInitParams {
		LPCWSTR _filename;

		

		InitData() {
		

		}


		InitData(LPCWSTR filename) {
			_filename = filename;
		}

	};

	virtual void load() = 0;
	virtual void unload() = 0;

	int getHeight() { return _height; }
	int getWidth() { return _width; }

	virtual void loadImage(LPCWSTR filename);

protected:
	int _width = 0;
	int _height = 0;
};

