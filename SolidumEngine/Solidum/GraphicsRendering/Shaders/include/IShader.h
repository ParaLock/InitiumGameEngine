#pragma once
#include "../../../sysInclude.h"

class mesh;
class Texture;
class MaterialPass;
class ILight;
class Transform;
class CameraComponent;
class GPUPipeline;
class IResource;
class GraphicsCommandList;
class RenderFlowGraphIOInterface;
class ShaderInputLayout;
class DynamicStruct;

class IShader {
public:
	virtual void updateDeferredLightUniforms(ILight* light) = 0;

	virtual void updateMaterialPassUniforms(MaterialPass* pass, RenderFlowGraphIOInterface* ioInterface) = 0;

	virtual void updatePointLightsForwardRendering(std::vector<ILight*> pointLights) = 0;
	virtual void updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights) = 0;

	virtual void updateModelUniforms(Transform* transform) = 0;
	virtual void updateCameraUniforms(CameraComponent* cam) = 0;

	virtual const std::map<std::string, std::pair<SHADER_TYPE, DynamicStruct*>>& getConstantBuffers() = 0;

	virtual ShaderInputLayout* getInputLayout() = 0;

	virtual void updateUniform(std::string varName, void * pData) = 0;
	virtual void updateGPU() = 0;

	virtual void execute(GraphicsCommandList* commandList) = 0;
};