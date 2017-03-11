#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../GraphicsRendering/Material/include/Material.h"
#include "../../../GraphicsRendering/Textures/include/Texture.h"

#include "../../../GraphicsRendering/RenderNode/include/MeshRenderNode.h"

class MeshComponent : public Component
{
private:
	std::vector<uint64_t> _renderNodes;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat);
	~MeshComponent();

	void update();
	void onEvent(EVENT_PTR evt);
};

