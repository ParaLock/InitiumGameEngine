#include "../include/PipelineCommand.h"


void PipelineSRBindCommand::execute()
{
	switch (_resourceType)
	{
	case SHADER_RESOURCE_TYPE::CONSTANT_BUFFER:

		PipelineFunctions::pipeline_bindConstantBuffer(_bindSlot, _parentShader, _sr->getParameter("GPUBUFFER"));

		break;
	case SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER:

		PipelineFunctions::pipeline_bindTextureSampler(_bindSlot, _parentShader, _sr->getParameter("TEXTURESAMPLER"));

		break;
	case SHADER_RESOURCE_TYPE::TEXTURE:

		PipelineFunctions::pipeline_bindTexture(_bindSlot, _parentShader, _sr->getParameter("TEXTURE"));

		break;
	default:
		break;
	}
}

void PipelineBufferBindCommand::execute()
{
	std::vector<void*> _rawBuffers;
	
	std::vector<GPUBuffer*> _buffersList;
	std::vector<UINT> _strides;

	for each(InitData::BufferBindInfo buffInfo in _bufferList) {
		
		_buffersList.push_back(buffInfo._buff);
		_strides.push_back(buffInfo._stride);
		
	}

	for each(GPUBuffer* buff in _buffersList) {
		_rawBuffers.push_back(buff->getParameter("BUFFER"));
	}

	PipelineFunctions::pipeline_bindBuffer(_rawBuffers, _strides, _type);
}

void PipelineILBindCommand::execute()
{
	ShaderInputLayout* inputLayout = (ShaderInputLayout*)_inputLayout;

	PipelineFunctions::pipeline_bindInputLayout(_inputLayout->getParameter("INPUT_LAYOUT"));
}

void PipelineSetBlendStateCommand::execute()
{
	PipelineFunctions::pipeline_set_blend_state(_blendState);
}

void PipelineSetDepthTestStateCommand::execute()
{
	PipelineFunctions::pipeline_set_depth_test_state(_depthTestState);
}

void PipelineRenderTargetCommand::execute()
{
	for each(InitData::RendertargetOP op in _bindInfo.rtOPList) {

		if (op._opType == RENDER_TARGET_OP_TYPE::CLEAR) {
			op._rt->Clear(0.0f, 0.0f, 0.0f, 0.0f);
		}

	}

	for each(InitData::InputRenderTargetBindInfo inputRT in _bindInfo.inputRTList) {

		void* tmpRT = inputRT._rt->getParameter("SHADERVIEW");

		PipelineFunctions::pipeline_bindRenderTargetAsSR(tmpRT, inputRT._targetShader, inputRT._bindSlot);
	}

	std::vector<void*> outputRTs;
	DepthStencil* outputRTDepthStencil = nullptr;

	for each(InitData::OutputRenderTargetBindInfo outputRT in _bindInfo.outputRTList) {

		outputRTs.push_back(outputRT._rt->getParameter("RENDERTARGET"));

		if (outputRT._depthStencil != nullptr) {
			outputRTDepthStencil = outputRT._depthStencil;
		}

	}

	for each(void* rt in outputRTs) {

		if (outputRTDepthStencil != nullptr)
			PipelineFunctions::pipeline_bindRenderTargetAsRT(outputRTs, outputRTDepthStencil->getParameter("STENCILVIEW"));
		else
			PipelineFunctions::pipeline_bindRenderTargetAsRT(outputRTs, nullptr);

	}
}

void PipelineSetPTCommand::execute()
{
	PipelineFunctions::pipeline_setPrimitiveTopology(_ptType);
}

void PipelineStateResetCommand::execute()
{
	PipelineFunctions::pipeline_reset();
}

void PipelineDrawIndexedCommand::execute()
{
	PipelineFunctions::pipeline_drawIndexed(_index, _numIndices);
}

void PipelineBindShaderCommand::execute()
{
	__shaderToBind->bind();
}

void PipelineSetRasterStateCommand::execute()
{
	PipelineFunctions::pipeline_set_raster_state(_state);
}

void PipelineSwapFrame::execute()
{
	PipelineFunctions::pipeline_swap_frame();
}

void PipelineClearDepthStencil::execute()
{
	_ds->clear(_depth);
}

void PipelineSetViewportCommand::execute()
{
	PipelineFunctions::pipeline_set_viewport(_viewport._maxDepth, 
		_viewport._minDepth, _viewport._width, _viewport._height);
}

void PipelineDrawInstancedCommand::execute()
{
	PipelineFunctions::pipeline_drawInstanced(_numIndices, _numInstances);
}
