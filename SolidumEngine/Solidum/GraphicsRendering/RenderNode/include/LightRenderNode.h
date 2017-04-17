#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"

#include "../../Shaders/include/Shader.h"

#include "../../Lights/include/Light.h"

#include "../../Lights/include/LightManager.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class LightRenderNode : public RenderNode
{
private:
	mesh* _orthoMesh;
public:
	LightRenderNode();
	~LightRenderNode();

	struct InitData : public IResourceBuilder {
		uint64_t _id;

		InitData(uint64_t id) {
			_id = id;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	ILight* getLight() { return (ILight*)_renderParams.getPerNodeParam_Light(); }

	bool isRenderViable();

	void render();
};

