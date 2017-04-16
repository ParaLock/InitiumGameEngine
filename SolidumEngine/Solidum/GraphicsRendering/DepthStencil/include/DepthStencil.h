#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"

class DepthStencil : public IResource
{
protected:
	int _width, _height;
public:
	DepthStencil();
	~DepthStencil();

	struct InitData : public IResourceBuilder {
		int _width, _height;

		InitData(int width, int height) {
			_width = width;
			_height = height;
		}
	};

	virtual void clear(float depth) = 0;

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	virtual void updateParameter(std::string varName, void *data) {};
	virtual void* getParameter(std::string varName) { return nullptr; };
};

