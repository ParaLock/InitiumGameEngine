#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../../EngineUtils/include/DynamicStruct.h"

#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/Resource.h"

#include "../../PipelineCommands/include/PipelineCommand.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../Window/include/window.h"

#include "../../GraphicsCommandList/include/GraphicsCommandList.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

class GPUPipelineElement {
public:
	SHADER_RESOURCE_TYPE type;
	SHADER_TYPE parentShader;

	IResource* core;

	int bindSlot;
	bool rt_isOutput;
};

class GPUPipelineOP {
public:
	PIPELINE_OP_TYPE opType;
	SHADER_RESOURCE_TYPE resType;

	IResource* opTarget;
};

class ResourcePool;

class GPUPipeline : public Resource<GPUPipeline, GenericFactory, ResourcePool>
{
private:
	std::map<std::string, GPUPipelineElement> *_elementList;

	std::list<GPUPipelineOP> *_opList;

	DepthStencil* _currentDepthStencil = nullptr;
	ShaderInputLayout* _currentInputLayout = nullptr;

	BLEND_STATE blendState = BLEND_STATE::BLENDING_OFF;
	DEPTH_TEST_STATE depthState = DEPTH_TEST_STATE::FULL_DISABLE;
	RASTER_STATE rasterState = RASTER_STATE::NORMAL;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

public:
	GPUPipeline();
	~GPUPipeline();

	struct InitData : public ResourceInitParams {
		LPCWSTR _filename;

		InitData() {}

		

		InitData(LPCWSTR filename) {
			_filename = filename;
		}
	};

	virtual void load();
	virtual void unload();

	void reset();

	void setRasterState(RASTER_STATE state);
	void setDepthTestState(DEPTH_TEST_STATE state);
	void setBlendState(BLEND_STATE state);

	void attachResource(IResource* res, std::string name, int index, SHADER_RESOURCE_TYPE type,
		SHADER_TYPE parentShader, bool isOutput);

	void attachOP(GPUPipelineOP op);

	void shaderSetVertexInputLayout(ShaderInputLayout* inputLayout) { _currentInputLayout = inputLayout; };

	void applyState(GraphicsCommandList* commandList);

	ShaderInputLayout* getInputLayout() { return _currentInputLayout; }

protected:
};

