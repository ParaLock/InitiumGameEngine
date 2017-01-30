#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../GraphicsRendering/Transform/include/Transform.h"

class MeshComponent : public Component
{
private:
	RenderOP* _op;
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat, Shader* shader);
	~MeshComponent();

	void update();
	void onEvent(IEvent* evt);
};

