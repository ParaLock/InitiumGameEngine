#pragma once

#include "../../../../GraphicsRendering/Mesh/include/mesh.h"

#include "../../../../GraphicsRendering/Material/include/Material.h"
#include "../../../../GraphicsRendering/Textures/include/Texture.h"
#include "../../../../GraphicsRendering/Shaders/include/Shader.h"

#include "../../Controllers/include/IController.h"
#include "../../../Transform/include/Transform.h"

#include "../../../../ResourceManagement/include/IResource.h"
#include "../../../../ResourceManagement/include/IResourceBuilder.h"

#include "../../../../sysInclude.h"

class SolidumObjectBuilder : public IResourceBuilder {
public:
	SolidumObjectBuilder() {

	}
};

class SolidumObject : public IResource
{
private:
	Transform* _transform = nullptr;
	mesh* _mesh = nullptr;
	Material* _mat = nullptr;
	Shader* _shader = nullptr;
public:
	SolidumObject(IResourceBuilder* builder);
	~SolidumObject();

	void attachMesh(mesh* newMesh);
	void attachMaterial(Material* newMat);
	void attachShader(Shader* newShader);

	Transform* getTransform() { return _transform; }

	Shader* getShader() { return _shader; }

	void draw();
};

