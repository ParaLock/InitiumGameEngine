#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../../EngineUtils/include/Timer.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class SkyBoxRenderNode : public RenderNode
{
public:
private:

	Vector4f _skydomeCenterColor;
	Vector4f _skydomeApexColor;

	Matrix4f _wvp;
public:
	SkyBoxRenderNode();
	~SkyBoxRenderNode();

	struct InitData : public IResourceBuilder {
		Vector4f _apexColor;
		Vector4f _centerColor;
		uint64_t _id;

		InitData(Vector4f apexColor,
			Vector4f centerColor, uint64_t id)
		{
			_apexColor = apexColor;
			_centerColor = centerColor;
			_id = id;
		}
	};

	void DeferredInit() {};

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	bool isRenderViable();

	void render();
};

