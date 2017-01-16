#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceManagement/include/IResourceManager.h"


#include "../../Directx11Rendering/dxShaders/include/dxShader.h"
#include "Shader.h"

class ShaderManager : public IResourceManager
{
public:
	ShaderManager();
	~ShaderManager();

	IResource* createResource(IResourceBuilder* builder, std::string name);
};

