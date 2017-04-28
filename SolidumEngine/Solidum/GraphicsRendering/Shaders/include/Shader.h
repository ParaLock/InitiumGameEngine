#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"

#include "../../../GraphicsRendering/GraphicsCommandList/include/GraphicsCommandList.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Lights/include/ILight.h"
#include "../../Material/include/Material.h"
#include "../../Transform/include/Transform.h"
#include "../../Mesh/include/mesh.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"

#include "IShader.h"

#include "../../../ResourceFramework/include/IResource.h"

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

	struct InitData : public IResourceBuilder {

		LPCWSTR _filename;
		SHADER_RENDER_TYPE _renderType = SHADER_RENDER_TYPE::INVALID;
		bool _genInputLayout = false;

		InitData(LPCWSTR filename, SHADER_RENDER_TYPE renderType, bool genInputLayout) {
			_filename = filename;
			_renderType = renderType;
			_genInputLayout = genInputLayout;
		};
	};

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	void setMiscResourceHook(IResource* res, std::string name);

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

	virtual void execute(GraphicsCommandList* commandList);

	SHADER_RENDER_TYPE getRenderMode() { return _renderType; }
};

