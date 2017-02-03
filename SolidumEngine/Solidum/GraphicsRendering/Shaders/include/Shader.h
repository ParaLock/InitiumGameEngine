#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Lights/include/ILight.h"
#include "../../Material/include/Material.h"
#include "../../Transform/include/Transform.h"
#include "../../Camera/include/camera.h"
#include "../../Mesh/include/mesh.h"

#include "../../../ResourceFramework/include/IResource.h"

class ShaderBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	ResourceManagerPool* _resManagerPool;

	ShaderBuilder(LPCWSTR filename, ResourceManagerPool* resManagerPool) {
		_filename = filename;
		_resManagerPool = resManagerPool;
	};
};

class Shader : public IResource
{
protected:
	std::map<std::string, DynamicStruct*> *_constantBufferMemberNameMap;

	GPUPipeline* _pipelineState = nullptr;

	ResourceManagerPool* _resManagerPool;
public:
	Shader();
	~Shader();

	virtual void load(IResourceBuilder* builder) = 0;
	virtual void unload() = 0;

	void setMesh(mesh* newMesh);

	void setModelTexture(Texture* tex);

	void updateMaterialUniforms(Material* mat);
	void updateLightUniforms(ILight* light);
	void updateModelUniforms(Transform* transform);
	void updateCameraUniforms(camera* cam);

	void updateUniform(std::string varName, void * pData);
	void updateGPU();

	virtual void attachPipeline(GPUPipeline* pipe) = 0;

	virtual void execute(int numIndices);
};

