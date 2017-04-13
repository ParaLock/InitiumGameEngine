#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"
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
		IShader* _shader;
		uint64_t _id;

		InitData(IShader* shader, uint64_t id) {
			_shader = shader;
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

