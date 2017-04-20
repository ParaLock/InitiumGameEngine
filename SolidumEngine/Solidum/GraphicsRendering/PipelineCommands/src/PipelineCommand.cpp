#include "../include/PipelineCommand.h"


PipelineCommand::PipelineCommand()
{
}


PipelineCommand::~PipelineCommand()
{
}

void PipelineSRBindCommand::execute()
{
	ResourceManagerPool* managerPool = ResourceManagerPool::getInstance();

	switch (_resourceType)
	{
	case SHADER_RESOURCE_TYPE::SHADER_CONSTANT_BUFFER:

		PipelineFunctions::pipeline_bindConstantBuffer(_bindSlot, _parentShader, _sr->getParameter("GPUBUFFER"));

		break;
	case SHADER_RESOURCE_TYPE::SHADER_TEX_SAMPLER:

		PipelineFunctions::pipeline_bindTextureSampler(_bindSlot, _parentShader, _sr->getParameter("TEXTURESAMPLER"));

		break;
	case SHADER_RESOURCE_TYPE::SHADER_TEXTURE_HOOK:

		PipelineFunctions::pipeline_bindTexture(_bindSlot, _parentShader, _sr->getParameter("TEXTURE"));

		break;
	default:
		break;
	}
}

void PipelineBufferBindCommand::execute()
{
	std::vector<void*> _rawBuffers;

	for each(GPUBuffer* buff in _buffers) {
		_rawBuffers.push_back(buff->getParameter("BUFFER"));
	}

	PipelineFunctions::pipeline_bindBuffer(_rawBuffers, _strides, _buffType);
}

void PipelineILBindCommand::execute()
{
	ShaderInputLayout* inputLayout = _inputLayout->getCore<ShaderInputLayout>();

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

	if (_op == RENDER_TARGET_OP_TYPE::BIND_AS_INPUT) {
		for each(IResource* rt in _involvedRTList) {

			RenderTarget* renderTarget = rt->getCore<RenderTarget>();

			void* tmpRT = renderTarget->getParameter("SHADERVIEW");

			PipelineFunctions::pipeline_bindRenderTargetAsSR(tmpRT, _parentShader, _bindSlot);
		}
	}

	if (_op == RENDER_TARGET_OP_TYPE::BIND_AS_OUTPUT) {

		std::vector<void*> pRts;

		for each(IResource* res in _involvedRTList) {
			pRts.push_back(res->getParameter("RENDERTARGET"));
		}

		if(_depthStencil != nullptr)
			PipelineFunctions::pipeline_bindRenderTargetAsRT(pRts, _depthStencil->getParameter("STENCILVIEW"));
		else
			PipelineFunctions::pipeline_bindRenderTargetAsRT(pRts, nullptr);
		
	}

	if (_op == RENDER_TARGET_OP_TYPE::CLEAR) {
		for each(IResource* rt in _involvedRTList) {

			rt->getCore<RenderTarget>()->Clear(0.0f, 0.0f, 0.0f, 0.0f);
		}
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
	__bindFunc();
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
