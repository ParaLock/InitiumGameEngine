#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"

#include "../../../GraphicsRendering/GraphicsCommandList/include/GraphicsCommandList.h"

#include "../../../ResourceFramework/include/ResourceInitParams.h"

#include "../../Lights/include/ILight.h"
#include "../../Material/include/Material.h"
#include "../../Transform/include/Transform.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"

#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../EngineUtils/include/DynamicStruct.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "ShaderFactory.h"

#include "IShader.h"

class MaterialPass;
class ResourcePool;

class Shader : public IShader, public Resource<Shader, ShaderFactory, ResourcePool>
{
protected:
	ShaderInputLayout* _vertexInputLayout;

	std::list<DynamicStruct*> _constantBufferList;

	std::map<std::string, DynamicStruct*> _varNameToConstantBuffer;
public:
	Shader();
	~Shader();

	struct InitData : public ResourceInitParams {

		InitData() {}

		std::string* _shaderCode;
		bool _genInputLayout = false;

		ResourceCreator* _resCreator;

		InitData(std::string* shaderCode, bool genInputLayout, ResourceCreator* resCreator) :
			_resCreator(resCreator)
		{
			_shaderCode = shaderCode;
			_genInputLayout = genInputLayout;
		};
	};

	virtual void load() = 0;
	virtual void unload() = 0;

	void updateMaterialPassUniforms(MaterialPass* pass, RenderFlowGraphIOInterface* ioInterface);

	void updateDeferredLightUniforms(ILight* light);

	void updatePointLightsForwardRendering(std::vector<ILight*> pointLights);
	void updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights);

	void updateModelUniforms(Transform* transform);
	void updateCameraUniforms(CameraComponent* cam);

	ShaderInputLayout* getInputLayout() { return _vertexInputLayout; }

	const std::list<DynamicStruct*>& getConstantBuffers() { return _constantBufferList; }

	void updateUniform(std::string& varName, void * pData);
	void updateGPU();

	virtual void execute(GraphicsCommandList* commandList);
protected:
};

