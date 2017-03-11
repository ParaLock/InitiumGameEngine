#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../../EngineUtils/include/DynamicStruct.h"

#include "../../../ResourceFramework/include/IResourceManager.h"
#include "../../../ResourceFramework/include/ResourceManagerPool.h"
#include "../../../ResourceFramework/include/IResource.h"

#include "../../PipelineCommand/include/PipelineCommand.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../PipelineCommandQueue/include/PipelineCommandQueue.h"

class GPUPipelineBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	PipelineCommandQueue* _commandQueue;

	GPUPipelineBuilder(LPCWSTR filename, PipelineCommandQueue* commandQueue) {
		_filename = filename;
		_commandQueue = commandQueue;
	}
};

class GPUPipelineElement {
public:
	SHADER_RESOURCE_TYPE type;
	SHADER_TYPE parentShader;

	IResource* core;

	int bindSlot;
	bool isOutput;
};

class GPUPipelineOP {
public:
	GPUPIPELINE_OP_TYPE opType;
	SHADER_RESOURCE_TYPE resType;

	IResource* opTarget;
};

class GPUPipeline : public IResource
{
private:
	int renderTargetCount = 0;
	int texSamplerCount = 0;
	int texHookCount = 0;

	PipelineCommandQueue* _parentCommandQueue;

	std::map<std::string, DynamicStruct*> *_constantBufferMemberNameMap;
	std::map<std::string, GPUPipelineElement*> *_elementList;

	std::list<GPUPipelineOP> *_opList;

	IResource* _currentInputLayout = nullptr;

	BLEND_STATE blendState = BLEND_STATE::BLENDING_OFF;
	DEPTH_TEST_STATE depthState = DEPTH_TEST_STATE::FULL_DISABLE;
	RASTER_STATE rasterState = RASTER_STATE::NORMAL;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

public:
	GPUPipeline();
	~GPUPipeline();

	virtual void load(IResourceBuilder* builder);
	virtual void unload();

	void reset();

	void setRasterState(RASTER_STATE state);
	void setDepthTestState(DEPTH_TEST_STATE state);
	void setBlendState(BLEND_STATE state);

	void setHookResource(IResource* res, std::string name);

	void attachResource(IResource* res, std::string name, SHADER_RESOURCE_TYPE type,
		SHADER_TYPE parentShader, bool isOutput);

	void attachOP(GPUPipelineOP op);

	void shaderSetVertexInputLayout(IResource* inputLayout) { _currentInputLayout = inputLayout; };

	void applyState();

	PipelineCommandQueue* getParentCommandQueue() { return _parentCommandQueue; }

	std::map<std::string, DynamicStruct*>* getVarToBuffMap() { return _constantBufferMemberNameMap; };
};

