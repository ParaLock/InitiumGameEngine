#pragma once
#ifndef _PIPELINE_COMMAND_H
#define _PIPELINE_COMMAND_H

#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "PipelineFunctions.h"

#include "../../Viewport/include/Viewport.h"

class IResource;

class PipelineCommand : public GraphicsCommand
{
public:
	PipelineCommand();
	~PipelineCommand();
};

class PipelineSRBindCommand : public PipelineCommand {
private:
	int _bindSlot = 0;

	IResource* _sr;

	SHADER_RESOURCE_TYPE _resourceType = SHADER_RESOURCE_TYPE::INVALID;
	SHADER_TYPE _parentShader = SHADER_TYPE::INVALID;
public:

	PipelineSRBindCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SR; }

	struct InitData : public IResourceBuilder {

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

	void load(std::shared_ptr<IResourceBuilder> builder) {

		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_resourceType = realBuilder->_resourceType;
		_bindSlot = realBuilder->_bindSlot;
		_sr = realBuilder->_sr;
		_parentShader = realBuilder->_parentShader;
	}

	void execute();
};

class PipelineBufferBindCommand : public PipelineCommand {
private:
	GPUBuffer* _buffer;
	
	UINT _offset;
	UINT _stride;
	BUFFER_TYPE _buffType;
public:
	PipelineBufferBindCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER; }
	

	struct InitData : public IResourceBuilder {
		GPUBuffer* _buffer;
		BUFFER_TYPE _gpuBufferType;

		UINT _offset;
		UINT _stride;

		InitData(GPUBuffer* buffer, UINT offset, UINT stride) {
			_gpuBufferType = buffer->getBuffType();

			_buffer = buffer;
			_offset = offset;
			_stride = stride;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_buffType = realBuilder->_gpuBufferType;

		_buffer = realBuilder->_buffer;
		_offset = realBuilder->_offset;
		_stride = realBuilder->_stride;
	}

	void unload() { _buffType = BUFFER_TYPE::INVALID; }

	void execute();
};

class PipelineILBindCommand : public PipelineCommand {
private:
	IResource* _inputLayout;
public:
	PipelineILBindCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_INPUT_LAYOUT; }

	struct InitData : public IResourceBuilder {
		IResource* _inputLayout;

		InitData(IResource* inputLayout) {
			_inputLayout = inputLayout;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_inputLayout = realBuilder->_inputLayout;
	}

	void execute();
};

class PipelineSetPTCommand : public PipelineCommand {
private:
	PRIMITIVE_TOPOLOGY _ptType;
public:

	PipelineSetPTCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_PRIMITIVE_TOPOLOGY; }

	struct InitData : public IResourceBuilder {

		PRIMITIVE_TOPOLOGY _ptType;

		InitData(PRIMITIVE_TOPOLOGY ptType) {
			_ptType = ptType;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_ptType = realBuilder->_ptType;
	}

	void execute();
};

class PipelineSetBlendStateCommand : public PipelineCommand {
private:
	BLEND_STATE _blendState;
public:
	PipelineSetBlendStateCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_BLEND_STATE; }

	struct InitData : public IResourceBuilder {
		BLEND_STATE _blendState;
		
		InitData(BLEND_STATE blendState) {
			_blendState = blendState;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_blendState = realBuilder->_blendState;
	}

	void execute();
};

class PipelineSetDepthTestStateCommand : public PipelineCommand {
private:
	DEPTH_TEST_STATE _depthTestState;
public:
	PipelineSetDepthTestStateCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_DEPTH_TEST_STATE; }

	struct InitData : public IResourceBuilder {
		DEPTH_TEST_STATE _depthTestState;

		InitData(DEPTH_TEST_STATE depthTestState) {
			_depthTestState = depthTestState;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_depthTestState = realBuilder->_depthTestState;
	}

	void execute();
};

class PipelineSetRasterStateCommand : public PipelineCommand {
private:
	RASTER_STATE _state;
public:
	PipelineSetRasterStateCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_RASTER_STATE; }

	struct InitData : public IResourceBuilder {
		RASTER_STATE _state;

		InitData(RASTER_STATE state) {
			_state = state;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_state = realBuilder->_state;
	}

	void execute();
};

class PipelineSetViewportCommand : public PipelineCommand {
private:
	Viewport _viewport;
public:
	PipelineSetViewportCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VIEWPORT_STATE; }

	struct InitData : public IResourceBuilder {

		Viewport _viewport;

		InitData(Viewport viewport) : _viewport(viewport) {
			
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_viewport = realBuilder->_viewport;
	}

	void execute();
};

class PipelineRenderTargetCommand : public PipelineCommand {
private:
	int _bindSlot;

	bool _bindDS;

	DepthStencil* _depthStencil;

	SHADER_TYPE _parentShader;

	std::list<RenderTarget*> _involvedRTList;

	RENDER_TARGET_OP_TYPE _op;
public:

	PipelineRenderTargetCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_RENDER_TARGET_COMMAND; }

	struct InitData : public IResourceBuilder {
		int _bindSlot;
		DepthStencil* _depthStencil;
		SHADER_TYPE _parentShader;
		std::list<RenderTarget*> _involvedRTList;
		RENDER_TARGET_OP_TYPE _op;

		InitData(int bindSlot, SHADER_TYPE parentShader, 
			std::list<RenderTarget*> involvedRTList,
				RENDER_TARGET_OP_TYPE op, 
			DepthStencil* depthStencil)
		{
			_depthStencil = depthStencil;
			_parentShader = parentShader;
			_bindSlot = bindSlot;
			_involvedRTList = involvedRTList;
			_op = op;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {

		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_parentShader = realBuilder->_parentShader;
		_bindSlot = realBuilder->_bindSlot;
		_depthStencil = realBuilder->_depthStencil;
		_involvedRTList = realBuilder->_involvedRTList;

		_op = realBuilder->_op;
	}

	void unload() {
	
		_involvedRTList.clear();
	}

	void execute();
};

class PipelineSwapFrame : public PipelineCommand {
private:
public:
	PipelineSwapFrame() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_SWAPFRAME; }

	void load(std::shared_ptr<IResourceBuilder> builder) {}

	void execute();
};

class PipelineClearDepthStencil : public PipelineCommand {
private:
	DepthStencil* _ds;
	float _depth;
public:
	PipelineClearDepthStencil() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_CLEAR_DEPTH_BUFFER; }

	struct InitData : public IResourceBuilder {
		DepthStencil* _ds;
		float _depth;

		InitData(DepthStencil* ds, float depth) {
			_ds = ds;
			_depth = depth;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_ds = realBuilder->_ds;
		_depth = realBuilder->_depth;
	}

	void execute();
};

class PipelineBindShaderCommand : public PipelineCommand {
private:
	std::function<void()> __bindFunc;
public:
	PipelineBindShaderCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SHADERS; }

	struct InitData : public IResourceBuilder {
		std::function<void()> _bindFunction;

		InitData(std::function<void()> bindFunction) {

			_bindFunction = bindFunction;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {

		InitData* realBuilder = static_cast<InitData*>(builder.get());

		__bindFunc = realBuilder->_bindFunction;

		int debugPoint = -1;
	}

	void unload() {
		__bindFunc = std::function<void()>();
	}

	void execute();
};

class PipelineDrawIndexedCommand : public PipelineCommand {
private:
	int _index;
	int _numIndices;
public:
	PipelineDrawIndexedCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED; }

	struct InitData : public IResourceBuilder {
		int _index;
		int _numIndices;

		InitData(int index, int _umIndices) {
			_index = index;
			_numIndices = _umIndices;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_index = realBuilder->_index;
		_numIndices = realBuilder->_numIndices;
	}

	void execute();

};

class PipelineStateResetCommand : public PipelineCommand {
private:
public:
	PipelineStateResetCommand() { _type = GRAPHICS_COMMAND_TYPE::PIPELINE_RESET; }

	void load(std::shared_ptr<IResourceBuilder> builder) {}

	void execute();
};

#endif