#pragma once
#ifndef _PIPELINE_COMMAND_H
#define _PIPELINE_COMMAND_H

#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"

#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "PipelineFunctions.h"

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
	PipelineSRBindCommand(int bindSlot, IResource* sr, SHADER_TYPE parentShader, SHADER_RESOURCE_TYPE resType) {
		_resourceType = resType;
		_bindSlot = bindSlot;
		_sr = sr;
		_parentShader = parentShader;
	}

	void execute();
};

class PipelineBufferBindCommand : public PipelineCommand {
private:
	IResource* _buffer;
	
	UINT _offset;
	UINT _stride;
public:
	PipelineBufferBindCommand(IResource* buffer, UINT offset, UINT stride) {
		_buffer = buffer;
		_offset = offset;
		_stride = stride;
	}

	void execute();
};

class PipelineILBindCommand : public PipelineCommand {
private:
	IResource* _inputLayout;
public:
	PipelineILBindCommand(IResource* inputLayout) {
		_inputLayout = inputLayout;
	}

	void execute();
};

class PipelineSetPTCommand : public PipelineCommand {
private:
	PRIMITIVE_TOPOLOGY _ptType;
public:

	PipelineSetPTCommand(PRIMITIVE_TOPOLOGY ptType) {
		_ptType = ptType;
	}

	void execute();
};

class PipelineSetBlendStateCommand : public PipelineCommand {
private:
	BLEND_STATE _blendState;
public:
	PipelineSetBlendStateCommand(BLEND_STATE blendState) {
		_blendState = blendState;
	}

	void execute();
};

class PipelineSetDepthTestStateCommand : public PipelineCommand {
private:
	DEPTH_TEST_STATE _depthTestState;
public:
	PipelineSetDepthTestStateCommand(DEPTH_TEST_STATE depthState) {
		_depthTestState = depthState;
	}

	void execute();
};

class PipelineSetRasterStateCommand : public PipelineCommand {
private:
	RASTER_STATE _state;
public:
	PipelineSetRasterStateCommand(RASTER_STATE state) {
		_state = state;
	}

	void execute();
};

class PipelineRenderTargetCommand : public PipelineCommand {
private:
	int _bindSlot;

	bool _bindDS;

	SHADER_TYPE _parentShader;

	std::vector<IResource*> _involvedRTList;

	RENDER_TARGET_OP_TYPE _op;
public:

	PipelineRenderTargetCommand(RENDER_TARGET_OP_TYPE op, SHADER_TYPE parentShader, int bindSlot, bool bindDS,
		std::list<IResource*> involvedRTs) {

		_parentShader = parentShader;

		_bindSlot = bindSlot;

		_bindDS = bindDS;

		_op = op;

		for each(IResource* rt in involvedRTs) {
			_involvedRTList.push_back(rt);
		}
	}

	void execute();
};

class PipelineSwapFrame : public PipelineCommand {
private:
public:
	void execute();
};

class PipelineClearDepthStencil : public PipelineCommand {
private:
public:

	void execute();
};

class PipelineBindShaderCommand : public PipelineCommand {
private:
	std::function<void()> _bindFunction;
public:
	PipelineBindShaderCommand(std::function<void()> bindFunction) {
		_bindFunction = bindFunction;
	}

	void execute();
};

class PipelineDrawIndexedCommand : public PipelineCommand {
private:
	int _index;
	int _numIndices;
public:

	PipelineDrawIndexedCommand(int index, int numIndices) {
		_index = index;
		_numIndices = numIndices;
	}

	void execute();

};

class PipelineStateResetCommand : public PipelineCommand {
private:
public:

	void execute();
};

#endif