#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"

#include "../../../GraphicsRendering/GraphicsCommandList/include/GraphicsCommandList.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Lights/include/ILight.h"
#include "../../Material/include/Material.h"
#include "../../Transform/include/Transform.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"

#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"

#include "IShader.h"

#include "../../../ResourceFramework/include/IResource.h"

class MaterialPass;

class Shader : public IShader, public IResource
{
protected:
	ShaderInputLayout* _vertexInputLayout;

	std::map<std::string, std::pair<SHADER_TYPE, DynamicStruct*>> _varNameToConstantBuffer;
public:
	Shader();
	~Shader();

	struct InitData : public IResourceBuilder {

		std::string& _shaderCode;
		bool _genInputLayout = false;

		InitData(std::string& shaderCode, bool genInputLayout) :
			_shaderCode(shaderCode)
		{
			_genInputLayout = genInputLayout;
		};
	};

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	void updateMaterialPassUniforms(MaterialPass* pass, RenderFlowGraphIOInterface* ioInterface);

	void updateDeferredLightUniforms(ILight* light);

	void updatePointLightsForwardRendering(std::vector<ILight*> pointLights);
	void updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights);

	void updateModelUniforms(Transform* transform);
	void updateCameraUniforms(CameraComponent* cam);

	ShaderInputLayout* getInputLayout() { return _vertexInputLayout; }

	const std::map<std::string, std::pair<SHADER_TYPE, DynamicStruct*>>& getConstantBuffers() { return _varNameToConstantBuffer; }

	void updateUniform(std::string varName, void * pData);
	void updateGPU();

	virtual void execute(GraphicsCommandList* commandList);
};

