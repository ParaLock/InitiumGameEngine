#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"
#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "DepthStencilFactory.h"

class ResourcePool;

class DepthStencil : public Resource<DepthStencil, DepthStencilFactory, ResourcePool>
{
public:
	DepthStencil();
	~DepthStencil();

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		int _width, _height;

		InitData(int width, int height) {
			_width = width;
			_height = height;
		}
	};

	virtual void clear(float depth) = 0;

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void updateParameter(std::string varName, void *data) {};
	virtual void* getParameter(std::string varName) { return nullptr; };
protected:
	int _width, _height;
};

