#pragma once
#ifndef _PIPELINE_COMMAND_H
#define _PIPELINE_COMMAND_H

#include "../../../sysInclude.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "../../Viewport/include/Viewport.h"

#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../DepthStencil/include/DepthStencil.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../../SolidumAPI/core_interfaces/IShader.h"

#include "PipelineFunctions.h"


//DECL_GRAPHICS_COMMAND(PipelineSRBindCommand,
//class DataPolicy {
//public:
//
//	struct InitData : public ResourceInitParams {
//
//		InitData() {
//		
//			int test = 1;
//		}
//
//		IResource* _sr = nullptr;
//		int _bindSlot;
//		SHADER_RESOURCE_TYPE _resourceType;
//		SHADER_TYPE _parentShader;
//
//		InitData(IResource* sr, int bindSlot, SHADER_RESOURCE_TYPE resourceType,
//			SHADER_TYPE parentShader)
//		{
//			_sr = sr;
//			_bindSlot = bindSlot;
//
//			_resourceType = resourceType;
//			_parentShader = parentShader;
//		}
//	};
//
//	int _bindSlot = 0;
//
//	IResource* _sr;
//
//	SHADER_RESOURCE_TYPE _resourceType = SHADER_RESOURCE_TYPE::INVALID_SR;
//	SHADER_TYPE _parentShader = SHADER_TYPE::INVALID_ST;
//
//};,
//class LoadPolicy {
//public:
//	static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//
//		dataOut->_resourceType = initParams->_resourceType;
//		dataOut->_bindSlot = initParams->_bindSlot;
//
//		dataOut->_sr = initParams->_sr;
//		dataOut->_parentShader = initParams->_parentShader;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	static void EXECUTE(DataPolicy* data) {
//
//		switch (data->_resourceType)
//		{
//		case SHADER_RESOURCE_TYPE::CONSTANT_BUFFER:
//
//			PipelineFunctions::pipeline_bindConstantBuffer(data->_bindSlot, data->_parentShader, data->_sr->getParameter("GPUBUFFER"));
//
//			break;
//		case SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER:
//
//			PipelineFunctions::pipeline_bindTextureSampler(data->_bindSlot, data->_parentShader, data->_sr->getParameter("TEXTURESAMPLER"));
//
//			break;
//		case SHADER_RESOURCE_TYPE::TEXTURE:
//
//			PipelineFunctions::pipeline_bindTexture(data->_bindSlot, data->_parentShader, data->_sr->getParameter("TEXTURE"));
//
//			break;
//		default:
//			break;
//		}
//
//	}
//};);

class PipelineSRBindCommand : public GraphicsCommand<PipelineSRBindCommand> {
private:
	int _bindSlot = 0;

	IResource* _sr;

	SHADER_RESOURCE_TYPE _resourceType = SHADER_RESOURCE_TYPE::INVALID_SR;
	SHADER_TYPE _parentShader = SHADER_TYPE::INVALID_ST;
public:

	PipelineSRBindCommand() {}

	struct InitData : public ResourceInitParams {

		InitData() {}

		IResource* _sr;
		int _bindSlot;
		SHADER_RESOURCE_TYPE _resourceType;
		SHADER_TYPE _parentShader;

		InitData(IResource* sr, int bindSlot, SHADER_RESOURCE_TYPE resourceType, 
			SHADER_TYPE parentShader) 
		{
			_sr = sr;

			_bindSlot = bindSlot;
			_resourceType = resourceType;
			_parentShader = parentShader;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {

		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_resourceType = realBuilder->_resourceType;
		_bindSlot = realBuilder->_bindSlot;
		_sr = realBuilder->_sr;
		_parentShader = realBuilder->_parentShader;
	}

	void execute();

protected:
};


//DECL_GRAPHICS_COMMAND(PipelineBufferBindCommand,
//class DataPolicy {
//public:
//
//	struct InitData : public ResourceInitParams {
//
//		InitData() {}
//
//		struct BufferBindInfo {
//
//			BufferBindInfo(GPUBuffer* buff, UINT offset, UINT stride) {
//				_buff = buff;
//				_offset = offset;
//				_stride = stride;
//			}
//
//			GPUBuffer* _buff;
//			UINT _offset;
//			UINT _stride;
//		};
//
//		std::vector<BufferBindInfo> _bufferList;
//
//		BUFFER_TYPE _type;
//
//		InitData(std::vector<BufferBindInfo> buffs) {
//
//			if (!_bufferList.empty()) _type = _bufferList.at(0)._buff->getBuffType();
//
//			_bufferList = buffs;
//		}
//	};
//
//	BUFFER_TYPE _type;
//	std::vector<InitData::BufferBindInfo> _bufferList;
//
//};,
//class LoadPolicy {
//public:
//	static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//
//		dataOut->_bufferList = initParams->_bufferList;
//		dataOut->_type = initParams->_type;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	static void EXECUTE(DataPolicy* data) {
//
//		std::vector<void*> _rawBuffers;
//
//		std::vector<GPUBuffer*> _buffersList;
//		std::vector<UINT> _strides;
//
//		for each(DataPolicy::InitData::BufferBindInfo buffInfo in data->_bufferList) {
//
//			_buffersList.push_back(buffInfo._buff);
//			_strides.push_back(buffInfo._stride);
//
//		}
//
//		for each(GPUBuffer* buff in _buffersList) {
//			_rawBuffers.push_back(buff->getParameter("BUFFER"));
//		}
//
//		PipelineFunctions::pipeline_bindBuffer(_rawBuffers, _strides, data->_type);
//
//	}
//};);


class PipelineBufferBindCommand : public GraphicsCommand<PipelineBufferBindCommand> {

public:
	PipelineBufferBindCommand() { }
	
	struct InitData : public ResourceInitParams {

		InitData() {}

		

		struct BufferBindInfo {

			BufferBindInfo(GPUBuffer* buff, UINT offset, UINT stride) {
				_buff = buff;
				_offset = offset;
				_stride = stride;
			}

			GPUBuffer* _buff;
			UINT _offset;
			UINT _stride;
		};

		std::vector<BufferBindInfo> _bufferList;

		BUFFER_TYPE _type;


		InitData(std::vector<BufferBindInfo>& buffs) {
			
			_bufferList = buffs;

			if (!_bufferList.empty()) _type = _bufferList.at(0)._buff->getBuffType();

		}

	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_bufferList = realBuilder->_bufferList;

		_type = realBuilder->_type;
	}

	void unload() {}

	void execute();

private:
	BUFFER_TYPE _type;
	std::vector<InitData::BufferBindInfo> _bufferList;
protected:
};

//DECL_GRAPHICS_COMMAND(PipelineILBindCommand,
//class DataPolicy {
//public:
//
//	struct InitData : public ResourceInitParams {
//
//		InitData() {}
//
//		IResource* _inputLayout;
//
//		InitData(IResource* inputLayout) {
//			_inputLayout = inputLayout;
//		}
//	};
//
//	IResource* _inputLayout;
//
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_inputLayout = initParams->_inputLayout;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//
//		PipelineFunctions::pipeline_bindInputLayout(data->_inputLayout->getParameter("INPUT_LAYOUT"));
//
//	}
//};);

class PipelineILBindCommand : public GraphicsCommand<PipelineILBindCommand> {
private:
	IResource* _inputLayout;
public:

	PipelineILBindCommand() { }

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		IResource* _inputLayout;

		InitData(IResource* inputLayout) {
			_inputLayout = inputLayout;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_inputLayout = realBuilder->_inputLayout;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSetPTCommand,
//class DataPolicy {
//public:
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//		PRIMITIVE_TOPOLOGY _ptType;
//	
//		InitData(PRIMITIVE_TOPOLOGY ptType) {
//			_ptType = ptType;
//		}
//	};
//
//	PRIMITIVE_TOPOLOGY _ptType;
//
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_ptType = initParams->_ptType;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_setPrimitiveTopology(data->_ptType);
//	}
//};);

class PipelineSetPTCommand : public GraphicsCommand<PipelineSetPTCommand> {
private:
	PRIMITIVE_TOPOLOGY _ptType;
public:

	PipelineSetPTCommand() { }

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		PRIMITIVE_TOPOLOGY _ptType;

		InitData(PRIMITIVE_TOPOLOGY ptType) {
			_ptType = ptType;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_ptType = realBuilder->_ptType;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSetBlendStateCommand,
//class DataPolicy {
//public:
//	BLEND_STATE _blendState;
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//		BLEND_STATE _blendState;
//			
//		InitData(BLEND_STATE blendState) {
//			_blendState = blendState;
//		}
//	};
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_blendState = initParams->_blendState;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_set_blend_state(data->_blendState);
//	}
//};);


class PipelineSetBlendStateCommand : public GraphicsCommand<PipelineSetBlendStateCommand> {
private:
	BLEND_STATE _blendState;
public:

	PipelineSetBlendStateCommand() {}

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		BLEND_STATE _blendState;
		
		InitData(BLEND_STATE blendState) {
			_blendState = blendState;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_blendState = realBuilder->_blendState;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSetDepthTestStateCommand,
//class DataPolicy {
//public:
//	
//	DEPTH_TEST_STATE _depthTestState;
//	
//	struct InitData : public ResourceInitParams {
//			
//		InitData() {}
//	
//		DEPTH_TEST_STATE _depthTestState;
//	
//		InitData(DEPTH_TEST_STATE depthTestState) {
//			_depthTestState = depthTestState;
//		}
//	};
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_depthTestState = initParams->_depthTestState;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_set_depth_test_state(data->_depthTestState);
//	}
//};);



class PipelineSetDepthTestStateCommand : public GraphicsCommand<PipelineSetDepthTestStateCommand> {
private:
	DEPTH_TEST_STATE _depthTestState;
public:

	PipelineSetDepthTestStateCommand() {}

	struct InitData : public ResourceInitParams {
		
		InitData() {}

		

		DEPTH_TEST_STATE _depthTestState;

		InitData(DEPTH_TEST_STATE depthTestState) {
			_depthTestState = depthTestState;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_depthTestState = realBuilder->_depthTestState;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSetRasterStateCommand,
//class DataPolicy {
//public:
//	RASTER_STATE _state;
//
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//		RASTER_STATE _state;
//	
//		InitData(RASTER_STATE state) {
//			_state = state;
//		}
//	};
//	
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_set_raster_state(data->_state);
//	}
//};);

class PipelineSetRasterStateCommand : public GraphicsCommand<PipelineSetRasterStateCommand> {
private:
	RASTER_STATE _state;
public:

	PipelineSetRasterStateCommand() { }

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		RASTER_STATE _state;

		InitData(RASTER_STATE state) {
			_state = state;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_state = realBuilder->_state;
	}

	void execute();
protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSetViewportCommand,
//class DataPolicy {
//public:
//
//	Viewport _viewport;
//
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//		Viewport _viewport;
//	
//		InitData(Viewport viewport) : _viewport(viewport) {
//				
//		}
//	};
//
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_viewport = initParams->_viewport;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_set_viewport(data->_viewport._maxDepth,
//			data->_viewport._minDepth, data->_viewport._width, data->_viewport._height);
//	}
//};);

class PipelineSetViewportCommand : public GraphicsCommand<PipelineSetViewportCommand> {
private:
	Viewport _viewport;
public:
	PipelineSetViewportCommand() { }

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		Viewport _viewport;

		InitData(Viewport viewport) : _viewport(viewport) {
			
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_viewport = realBuilder->_viewport;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineRenderTargetCommand,
//class DataPolicy {
//public:
//
//	struct InitData : public ResourceInitParams {
//
//		struct RendertargetOP {
//
//			RendertargetOP(RENDER_TARGET_OP_TYPE type, RenderTarget* rt) {
//
//				_opType = type;
//				_rt = rt;
//			}
//
//			RENDER_TARGET_OP_TYPE _opType;
//
//			RenderTarget* _rt;
//
//		};
//
//		struct OutputRenderTargetBindInfo {
//
//			OutputRenderTargetBindInfo(DepthStencil* ds, RenderTarget* rt) {
//				_depthStencil = ds;
//				_rt = rt;
//			}
//
//			DepthStencil* _depthStencil;
//
//			RenderTarget* _rt;
//		};
//
//		struct InputRenderTargetBindInfo {
//
//			InputRenderTargetBindInfo(int bindSlot, SHADER_TYPE targetShader, RenderTarget* rt) {
//
//				_bindSlot = bindSlot;
//				_targetShader = targetShader;
//				_rt = rt;
//
//			}
//
//			int _bindSlot;
//
//			SHADER_TYPE _targetShader;
//
//			RenderTarget* _rt;
//		};
//
//		struct RenderTargetBindInfo {
//
//			std::list<RendertargetOP> rtOPList;
//
//			std::list<OutputRenderTargetBindInfo> outputRTList;
//			std::list<InputRenderTargetBindInfo> inputRTList;
//		};
//
//		RenderTargetBindInfo _bindInfo;
//
//		InitData() {}
//
//
//
//		InitData(RenderTargetBindInfo* bindInfo)
//		{
//			_bindInfo = *bindInfo;
//		}
//	};
//
//	InitData::RenderTargetBindInfo _bindInfo;
//
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_bindInfo = initParams->_bindInfo;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//
//		for each(DataPolicy::InitData::RendertargetOP op in data->_bindInfo.rtOPList) {
//
//			if (op._opType == RENDER_TARGET_OP_TYPE::CLEAR) {
//				op._rt->Clear(0.0f, 0.0f, 0.0f, 0.0f);
//			}
//
//		}
//
//		for each(DataPolicy::InitData::InputRenderTargetBindInfo inputRT in data->_bindInfo.inputRTList) {
//
//			void* tmpRT = inputRT._rt->getParameter("SHADERVIEW");
//
//			PipelineFunctions::pipeline_bindRenderTargetAsSR(tmpRT, inputRT._targetShader, inputRT._bindSlot);
//		}
//
//		std::vector<void*> outputRTs;
//		DepthStencil* outputRTDepthStencil = nullptr;
//
//		for each(DataPolicy::InitData::OutputRenderTargetBindInfo outputRT in data->_bindInfo.outputRTList) {
//
//			outputRTs.push_back(outputRT._rt->getParameter("RENDERTARGET"));
//
//			if (outputRT._depthStencil != nullptr) {
//				outputRTDepthStencil = outputRT._depthStencil;
//			}
//
//		}
//
//		for each(void* rt in outputRTs) {
//
//			if (outputRTDepthStencil != nullptr)
//				PipelineFunctions::pipeline_bindRenderTargetAsRT(outputRTs, outputRTDepthStencil->getParameter("STENCILVIEW"));
//			else
//				PipelineFunctions::pipeline_bindRenderTargetAsRT(outputRTs, nullptr);
//
//		}
//	}
//};);


class PipelineRenderTargetCommand : public GraphicsCommand<PipelineRenderTargetCommand> {
public:

	PipelineRenderTargetCommand() {}

	struct InitData : public ResourceInitParams {

		struct RendertargetOP {

			RendertargetOP(RENDER_TARGET_OP_TYPE type, RenderTarget* rt) {

				_opType = type;
				_rt = rt;
			}

			RENDER_TARGET_OP_TYPE _opType;

			RenderTarget* _rt;

		};

		struct OutputRenderTargetBindInfo {

			OutputRenderTargetBindInfo(DepthStencil* ds, RenderTarget* rt) {
				_depthStencil = ds;
				_rt = rt;
			}

			DepthStencil* _depthStencil;

			RenderTarget* _rt;
		};

		struct InputRenderTargetBindInfo {

			InputRenderTargetBindInfo(int bindSlot, SHADER_TYPE targetShader, RenderTarget* rt) {

				_bindSlot = bindSlot;
				_targetShader = targetShader;
				_rt = rt;

			}

			int _bindSlot;

			SHADER_TYPE _targetShader;

			RenderTarget* _rt;
		};

		struct RenderTargetBindInfo {

			std::list<RendertargetOP> rtOPList;

			std::list<OutputRenderTargetBindInfo> outputRTList;
			std::list<InputRenderTargetBindInfo> inputRTList;
		};

		RenderTargetBindInfo _bindInfo;

		InitData() {}

		

		InitData(RenderTargetBindInfo* bindInfo)
		{
			_bindInfo = *bindInfo;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {

		InitData* realBuilder = (InitData*)getContext()->getResourceInitParams();

		if (realBuilder->_bindInfo.rtOPList.size() > 0) {
			
			int test = 1;
		}

		_bindInfo = realBuilder->_bindInfo;

	}

	void unload() {
	
	}

	void execute();
private:

	InitData::RenderTargetBindInfo _bindInfo;

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineSwapFrame,
//class DataPolicy {
//public:
//	struct InitData : public ResourceInitParams {
//
//
//
//		InitData() {}
//	};
//
//
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_swap_frame();
//	}
//};);

class PipelineSwapFrame : public GraphicsCommand<PipelineSwapFrame> {
private:
public:

	PipelineSwapFrame() {}

	struct InitData : public ResourceInitParams {

		

		InitData() {}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineClearDepthStencil,
//class DataPolicy {
//public:
//	struct InitData : public ResourceInitParams {
//
//		DepthStencil* _ds;
//		float _depth;
//
//		InitData() {}
//
//		InitData(DepthStencil* ds, float depth) {
//			_ds = ds;
//			_depth = depth;
//		}
//	};
//
//	DepthStencil* _ds;
//	float _depth;
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_ds = initParams->_ds;
//
//		dataOut->_depth = initParams->_depth;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		data->_ds->clear(data->_depth);
//	}
//};);

class PipelineClearDepthStencil : public GraphicsCommand<PipelineClearDepthStencil> {
private:
	DepthStencil* _ds;
	float _depth;
public:

	PipelineClearDepthStencil() {}

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		DepthStencil* _ds;
		float _depth;

		InitData(DepthStencil* ds, float depth) {
			_ds = ds;
			_depth = depth;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_ds = realBuilder->_ds;

		_depth = realBuilder->_depth;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineBindShaderCommand,
//class DataPolicy {
//public:
//	struct InitData : public ResourceInitParams {
//
//		InitData() {}
//
//		IShader* _shaderToBind;
//
//		InitData(IShader* shaderToBind) {
//
//			_shaderToBind = shaderToBind;
//		}
//	};
//
//	IShader* __shaderToBind;
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->__shaderToBind = initParams->_shaderToBind;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		data->__shaderToBind->bind();
//	}
//};);

class PipelineBindShaderCommand : public GraphicsCommand<PipelineBindShaderCommand> {
private:
	IShader* __shaderToBind;
public:

	PipelineBindShaderCommand() {}

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		IShader* _shaderToBind;

		InitData(IShader* shaderToBind) {

			_shaderToBind = shaderToBind;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {

		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		__shaderToBind = realBuilder->_shaderToBind;

		int debugPoint = -1;
	}

	void unload() {
		__shaderToBind = nullptr;
	}

	void execute();

protected:
};

//DECL_GRAPHICS_COMMAND(PipelineDrawIndexedCommand,
//class DataPolicy {
//public:
//	int _index;
//	int _numIndices;
//
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//		int _index;
//		int _numIndices;
//	
//		InitData(int index, int _umIndices) {
//			_index = index;
//			_numIndices = _umIndices;
//		}
//	};
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_index = initParams->_index;
//		dataOut->_numIndices = initParams->_numIndices;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_drawIndexed(data->_index, data->_numIndices);
//	}
//};);

class PipelineDrawIndexedCommand : public GraphicsCommand<PipelineDrawIndexedCommand> {
private:
	int _index;
	int _numIndices;
public:

	PipelineDrawIndexedCommand() {}

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		int _index;
		int _numIndices;

		InitData(int index, int _umIndices) {
			_index = index;
			_numIndices = _umIndices;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_index = realBuilder->_index;
		_numIndices = realBuilder->_numIndices;
	}

	void execute();
protected:
};

//DECL_GRAPHICS_COMMAND(PipelineDrawInstancedCommand,
//class DataPolicy {
//public:
//	int _numInstances;
//	int _numIndices;
//
//	struct InitData : public ResourceInitParams {
//
//		InitData() {}
//
//		int _numIndices;
//		int _numInstances;
//
//		InitData(int numIndices, int numInstances) {
//
//			_numIndices = numIndices;
//			_numInstances = numInstances;
//		}
//	};
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_numInstances = initParams->_numInstances;
//		dataOut->_numIndices = initParams->_numIndices;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_drawInstanced(data->_numIndices, data->_numInstances);
//	}
//};);

class PipelineDrawInstancedCommand : public GraphicsCommand<PipelineDrawInstancedCommand> {
private:
	int _numInstances;
	int _numIndices;
public:

	PipelineDrawInstancedCommand() { }

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		int _numIndices;
		int _numInstances;

		InitData(int numIndices, int numInstances) {

			_numIndices = numIndices;
			_numInstances = numInstances;
		}
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_numInstances = realBuilder->_numInstances;
		_numIndices = realBuilder->_numIndices;
	}

	void execute();

protected:

};

//DECL_GRAPHICS_COMMAND(PipelineStateResetCommand,
//class DataPolicy {
//public:
//	struct InitData : public ResourceInitParams {
//	
//		InitData() {}
//	
//	};
//	
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		PipelineFunctions::pipeline_reset();
//	}
//};);

class PipelineStateResetCommand : public GraphicsCommand<PipelineStateResetCommand> {
private:
public:

	struct InitData : public ResourceInitParams {

		

		InitData() {}

	};

	PipelineStateResetCommand() { }

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {}

	void execute();

protected:
};

#endif