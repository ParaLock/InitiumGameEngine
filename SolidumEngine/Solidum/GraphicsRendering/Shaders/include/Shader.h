#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"
#include "../../GPUPipeline/include/GPUPipelineFactory.h"

#include "../../Lights/include/Light.h"
#include "../../Material/include/Material.h"
#include "../../../EngineCore/Transform/include/Transform.h"
#include "../../Camera/include/camera.h"
#include "../../Mesh/include/mesh.h"

class Shader
{
protected:
	std::map<std::string, DynamicBuffer*> *_uniformVarNameToBuff;

	GPUPipeline *_pipelineState;
public:
	Shader();
	~Shader();

	void setTexture(Texture *tex);
	void setMesh(mesh* newMesh);

	void updateMaterialUniforms(Material* mat);
	void updateLightUniforms(Light* light);
	void updateModelUniforms(Transform* transform);
	void updateCameraUniforms(camera* cam);

	void updateUniform(std::string varName, void * pData);
	void updateGPU();

	virtual void execute(int numIndices);
};

