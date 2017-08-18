#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../../EngineUtils/include/DynamicStruct.h"

#include "../../../../SolidumAPI/core_interfaces/IResource.h"
#include "../../../ResourceFramework/include/Resource.h"

#include "../../PipelineCommands/include/PipelineCommand.h"
#include "../../ShaderCommands/include/ShaderCommand.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../Window/include/window.h"

#include "../../GraphicsCommandList/include/GraphicsCommandList.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "../../../../SolidumAPI/core_interfaces/IGPUBuffer.h"

#include "../../../../SolidumAPI/core_interfaces/IGPUPipeline.h"
#include "../../../../SolidumAPI/core_objects/include/ShaderUniformGroup.h"


#include "../../../../SolidumAPI/core_interfaces/IShader.h"

enum class DRAW_MODE {
	INDEXED,
	INSTANCED
};

struct DrawModeIndexedInfo {
	DrawModeIndexedInfo(int numIndices) {
		_numIndices = numIndices;
	}

	DrawModeIndexedInfo() {}

	int _numIndices;
};

struct DrawModeInstancedInfo {

	DrawModeInstancedInfo(int numInstances, int numIndices) {
		_numInstances = numInstances;
		_numIndices = numIndices;
	}

	DrawModeInstancedInfo() {}

	int _numInstances;
	int _numIndices;

};

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

struct InstanceBufferBindInfo {

	InstanceBufferBindInfo(IGPUBuffer* instBuff, IGPUBuffer* vertexBuff, size_t instanceStride, size_t vertexStride) {

		_instBuffStride = instanceStride;
		_vertexBuffStride = vertexStride;
		_instanceBuff = instBuff;
		_vertexBuff = vertexBuff;
	}

	InstanceBufferBindInfo() {}

	size_t _instBuffStride;
	size_t _vertexBuffStride;

	IGPUBuffer* _instanceBuff;
	IGPUBuffer* _vertexBuff;
};

#define MAX_UNIFORM_GROUPS 8

class GPUPipeline : public Resource<GPUPipeline, GenericFactory, ResourcePool>, public IGPUPipeline
{
private:

	IShader* _renderShader = nullptr;

	DRAW_MODE _activeDrawMode;

	bool _pipelineStateResetAtCompletion;

	int _currentUniformGroupCount = 0;

	DrawModeInstancedInfo _drawModeInstancedInfo;
	DrawModeIndexedInfo _drawModeIndexedInfo;

	ShaderUniformGroup _shaderUniformGroups[MAX_UNIFORM_GROUPS];

	std::list<InstanceBufferBindInfo> _instanceBufferList;

	std::list<GPUPipelineElement> _elementList;

	std::list<GPUPipelineOP> _opList;

	DepthStencil* _currentDepthStencil = nullptr;
	IShaderInputLayout* _currentInputLayout = nullptr;

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

	void setDrawModeIndexed(int indexCount);
	void setDrawModeInstanced(int instanceCount, int numIndices);

	void addInstanceBuffer(IGPUBuffer* instanceBuff, IGPUBuffer* geoBuff, size_t instBuffStride, size_t vertexBuffStride);

	void setPipelineStateResetAtCompletion(bool state);

	void setShader(IShader* shader);
	void addShaderUniformGroup(ShaderUniformGroup& group);

	void attachResource(IResource* res, std::string name, int index, SHADER_RESOURCE_TYPE type,
		SHADER_TYPE parentShader, bool isOutput);

	void attachOP(GPUPipelineOP op);

	void shaderSetVertexInputLayout(IShaderInputLayout* inputLayout) { _currentInputLayout = inputLayout; };

	void applyState(IGraphicsCommandBlock* commandBlock);

	IShaderInputLayout* getInputLayout() { return _currentInputLayout; }

protected:
};

