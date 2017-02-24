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
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat);
	~MeshComponent();

	void update();
	void onEvent(EVENT_PTR evt);
};

