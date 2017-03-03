#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Lights/include/ILight.h"
#include "../../Material/include/Material.h"
#include "../../Transform/include/Transform.h"
#include "../../Mesh/include/mesh.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"

#include "IShader.h"

#include "../../../ResourceFramework/include/IResource.h"

class ShaderBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	SHADER_RENDER_TYPE _renderType = SHADER_RENDER_TYPE::INVALID;

	ShaderBuilder(LPCWSTR filename, SHADER_RENDER_TYPE renderType) {
		_filename = filename;
		_renderType = renderType;
	};
};

class MaterialPass;

class Shader : public IShader, public IResource
{
protected:
	std::map<std::string, DynamicStruct*> *_constantBufferMemberNameMap;

	SHADER_RENDER_TYPE _renderType;

	GPUPipeline* _pipelineState = nullptr;
public:
	Shader();
	~Shader();

	virtual void load(IResourceBuilder* builder) = 0;
	virtual void unload() = 0;

	void setMesh(mesh* newMesh);

	void setModelTexture(Texture* tex);

	void updateMaterialPassUniforms(MaterialPass* pass);
	void updateDeferredLightUniforms(ILight* light);

	void updatePointLightsForwardRendering(std::vector<ILight*> pointLights);
	void updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights);

	void updateModelUniforms(Transform* transform);
	void updateCameraUniforms(CameraComponent* cam);

	void updateUniform(std::string varName, void * pData);
	void updateGPU();

	virtual void attachPipeline(GPUPipeline* pipe) = 0;
	GPUPipeline* getPipeline() { return _pipelineState; }

	virtual void execute(int numIndices);

	SHADER_RENDER_TYPE getRenderMode() { return _renderType; }
};

