#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"

#include "../include/LightRenderNode.h"

#include "../../Material/include/Material.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class MeshRenderNode : public RenderNode
{
private:
public:
	MeshRenderNode();
	~MeshRenderNode();

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

	Transform* getTransform() { return _renderParams.getPerNodeParam_Transform(); }

	mesh* getMesh() { return _renderParams.getPerNodeParam_Mesh(); }

	bool isRenderViable();

	void render();
};

