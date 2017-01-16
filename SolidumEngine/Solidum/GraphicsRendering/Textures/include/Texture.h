#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/ActiveGraphicsAPI.h"

#include "../../../ResourceManagement/include/IResourceBuilder.h"

#include "../../../ResourceManagement/include/IResource.h"

class TextureBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;

	TextureBuilder(LPCWSTR filename) {
		_filename = filename;
	}
};

class Texture : public IResource
{
public:
	Texture();
	~Texture();

	virtual void loadImage(LPCWSTR filename);

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);
};

