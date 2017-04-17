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
	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	mesh* _mesh;
	Texture* _tex;
	Material* _mat;
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat, int index, IEntity* entity);
	~MeshComponent();

	void update(float delta);
	void onEvent(EVENT_PTR evt);
};

