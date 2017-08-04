#include "../include/GPUPipeline.h"


GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement>;
	_opList = new std::list<GPUPipelineOP>;
}


GPUPipeline::~GPUPipeline()
{
	delete _elementList;
	delete _opList;
}

void GPUPipeline::load()
{
}

void GPUPipeline::unload()
{
}

void GPUPipeline::reset()
{
	blendState = BLEND_STATE::BLENDING_OFF;

	_opList->clear();
	_elementList->clear();
}

void GPUPipeline::setRasterState(RASTER_STATE state)
{
	rasterState = state;
}

void GPUPipeline::setDepthTestState(DEPTH_TEST_STATE state)
{
	depthState = state;
}

void GPUPipeline::setBlendState(BLEND_STATE state)
{
	blendState = state;
}

void GPUPipeline::attachResource(IResource* res, std::string name, int index, SHADER_RESOURCE_TYPE type,
	SHADER_TYPE parentShader, bool isOutput)
{
	GPUPipelineElement newElement;

	newElement.rt_isOutput = isOutput;

	newElement.type = type;
	newElement.parentShader = parentShader;

	newElement.core = res;

	newElement.bindSlot = index;

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachOP(GPUPipelineOP op)
{
	_opList->push_back(op);
}

void GPUPipeline::applyState(GraphicsCommandList* commandList)
{
	PipelineRenderTargetCommand::InitData::RenderTargetBindInfo rtBindInfo;
	std::vector<RenderTarget*> outputRenderTargets;

	commandList->createCommand<PipelineSetPTCommand>
		(&PipelineSetPTCommand::InitData(PRIMITIVE_TOPOLOGY::TRANGLE_LIST));

	for (std::map<std::string, GPUPipelineElement>::iterator itr =
		_elementList->begin(); itr != _elementList->end(); ++itr)
	{

		GPUPipelineElement& element = itr->second;

		if (element.core != nullptr) {

			if (element.type == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {
				_currentDepthStencil = (DepthStencil*)element.core;
			}

			if (element.type == SHADER_RESOURCE_TYPE::TEXTURE) {

				commandList->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER) {

				commandList->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::CONSTANT_BUFFER) {

				commandList->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::GPU_BUFFER) {

				commandList->createCommand<PipelineBufferBindCommand>(&PipelineBufferBindCommand::InitData
					(std::vector<PipelineBufferBindCommand::InitData::BufferBindInfo>{
					
					PipelineBufferBindCommand::InitData::BufferBindInfo((GPUBuffer*)element.core, 0, _currentInputLayout->getDataStride())
				
				}));
			}

			if (element.type == SHADER_RESOURCE_TYPE::RENDER_TARGET) {

				if (element.rt_isOutput)
				{
					RenderTarget* realRT = (RenderTarget*)element.core;

					Viewport rtView = realRT->getViewport();
					
					commandList->createCommand<PipelineSetViewportCommand>(&PipelineSetViewportCommand::InitData(rtView));

					outputRenderTargets.push_back((RenderTarget*)element.core);
				}
				else {

					rtBindInfo.inputRTList.push_back(PipelineRenderTargetCommand::InitData::InputRenderTargetBindInfo
						(element.bindSlot, element.parentShader, (RenderTarget*)element.core));			
				}
			}
		}
	}

	if (_currentInputLayout != nullptr) {

		commandList->createCommand<PipelineILBindCommand>(&PipelineILBindCommand::InitData(_currentInputLayout));
	}

	commandList->createCommand<PipelineSetBlendStateCommand>(&PipelineSetBlendStateCommand::InitData(blendState));
	commandList->createCommand<PipelineSetDepthTestStateCommand>(&PipelineSetDepthTestStateCommand::InitData(depthState));
	commandList->createCommand<PipelineSetRasterStateCommand>(&PipelineSetRasterStateCommand::InitData((rasterState)));

	for (auto itr = _opList->begin(); itr != _opList->end(); itr++) {
		GPUPipelineOP op = *itr;
		
		if (op.opType == PIPELINE_OP_TYPE::CLEAR) {

			if (op.resType == SHADER_RESOURCE_TYPE::RENDER_TARGET) {

				rtBindInfo.rtOPList.push_back(PipelineRenderTargetCommand::InitData::RendertargetOP
					(RENDER_TARGET_OP_TYPE::CLEAR, (RenderTarget*)op.opTarget)); 
			}
		
			if (op.resType == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {
				
				commandList->createCommand<PipelineClearDepthStencil>
					(&PipelineClearDepthStencil::InitData((DepthStencil*)op.opTarget, 1.0f));
			}
		}

		if (op.opType == PIPELINE_OP_TYPE::SWAPFRAME) {

			commandList->createCommand<PipelineSwapFrame>(&PipelineSwapFrame::InitData());
		}
	}

	for each(RenderTarget* rt in outputRenderTargets) {

		rtBindInfo.outputRTList.push_back(PipelineRenderTargetCommand::InitData::OutputRenderTargetBindInfo
			(_currentDepthStencil, rt));
	}

	commandList->createCommand<PipelineRenderTargetCommand>(&PipelineRenderTargetCommand::InitData(&rtBindInfo));
}
