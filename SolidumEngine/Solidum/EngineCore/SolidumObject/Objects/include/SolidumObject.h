#pragma once

#include "../../../../GraphicsRendering/Textures/include/ITexture.h"
#include "../../../../GraphicsRendering/Textures/include/TextureFactory.h"

#include "../../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../../GraphicsRendering/Mesh/include/meshFactory.h"

#include "../../../../GraphicsRendering/Shaders/include/IShader.h"
#include "../../../../GraphicsRendering/Shaders/include/ShaderFactory.h"

#include "../../Controllers/include/IController.h"

#include "../../../Transform/include/Transform.h"

#include "../../../../sysInclude.h"

class SolidumObject
{
private:
	mesh* activeMesh;
	ITexture* activeTex;
	IShader* activeShader;

	Transform *transform;
public:
	SolidumObject();
	~SolidumObject();

	std::list<IController*> *attachedControllers;

	void setActiveMesh(std::string meshName) { activeMesh = meshFactory::requestMesh(meshName); };
	void setActiveTexture(std::string texName) { activeTex = TextureFactory::requestTexture(texName); };
	void setActiveShader(std::string shaderName) { activeShader = ShaderFactory::requestShader(shaderName); };

	mesh* getActiveMesh() { return activeMesh; };
	ITexture* getActiveTexture() { return activeTex; };
	IShader* getActiveShader() { return activeShader; };

	void AttachController(IController *controller);

	void Render();
};

