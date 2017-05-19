#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../../EngineUtils/include/Timer.h"

#include "../../RenderNode/include/LightRenderNode.h"
#include "../../RenderNode/include/MeshRenderNode.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class ShadowGenRenderNode : public RenderNode
{
private:
public:
	ShadowGenRenderNode();
	~ShadowGenRenderNode();
	
	struct InitData : public IResourceBuilder {

		uint64_t _id;

		InitData(uint64_t id) {
			_id = id;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	bool isRenderViable();

	void render();
};

