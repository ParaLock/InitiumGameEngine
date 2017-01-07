#pragma once

#include "../../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../../GraphicsRendering/Mesh/include/meshFactory.h"

#include "../../../../GraphicsRendering/Material/include/Material.h"
#include "../../../../GraphicsRendering/Textures/include/Texture.h"
#include "../../../../GraphicsRendering/Shaders/include/Shader.h"

#include "../../Controllers/include/IController.h"
#include "../../../Transform/include/Transform.h"

#include "../../../../sysInclude.h"

class SolidumObject
{
private:
	Transform* _transform = nullptr;
	Texture* _texture = nullptr;
	mesh* _mesh = nullptr;
	Material* _mat = nullptr;
	Shader* _shader = nullptr;
public:
	SolidumObject();
	~SolidumObject();

	void attachMesh(mesh* newMesh);
	void attachTexture(Texture* newTex);
	void attachMaterial(Material* newMat);
	void attachShader(Shader* newShader);

	Transform* getTransform() { return _transform; }

	Shader* getShader() { return _shader; }

	void draw();
};

