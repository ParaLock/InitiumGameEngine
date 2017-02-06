#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../GraphicsRendering/Material/include/Material.h"
#include "../../../GraphicsRendering/Textures/include/Texture.h"

class MeshComponent : public Component
{
private:
	mesh* _mesh;
	Texture* _tex;
	Material* _mat;

	Transform* _transform = nullptr;

	RenderDataStream *_graphicsStream = nullptr;
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat, std::string rendProcID);
	~MeshComponent();

	void update();
	void onEvent(EVENT_PTR evt);
};

