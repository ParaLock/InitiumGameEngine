#include "../include/GPUPipeline.h"


GPUPipeline::GPUPipeline()
{
	_pipelineStateResetAtCompletion = false;
}


GPUPipeline::~GPUPipeline()
{
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
	depthState = DEPTH_TEST_STATE::INVALID;
	rasterState = RASTER_STATE::NORMAL;

	_renderShader = nullptr;
	_pipelineStateResetAtCompletion = false;
	_currentInputLayout = nullptr;

	_currentUniformGroupCount = 0;
	_opList.clear();
	_elementList.clear();
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

void GPUPipeline::setDrawModeIndexed(int indexCount)
{
	_activeDrawMode = DRAW_MODE::INDEXED;

	_drawModeIndexedInfo._numIndices = indexCount;
}

void GPUPipeline::setDrawModeInstanced(int instanceCount, int numIndices)
{
	_activeDrawMode = DRAW_MODE::INSTANCED;

	_drawModeInstancedInfo._numIndices = numIndices;
	_drawModeInstancedInfo._numInstances = instanceCount;
}

void GPUPipeline::addInstanceBuffer(IGPUBuffer * instanceBuff, IGPUBuffer * geoBuff, size_t instBuffStride, size_t vertexBuffStride)
{
	_instanceBufferList.push_back(InstanceBufferBindInfo(instanceBuff, geoBuff, instBuffStride, vertexBuffStride));
}

void GPUPipeline::setPipelineStateResetAtCompletion(bool state)
{
	_pipelineStateResetAtCompletion = state;
}

void GPUPipeline::setShader(IShader * shader)
{
	_renderShader = shader;

	_currentInputLayout = _renderShader->getInputLayout();
}

void GPUPipeline::addShaderUniformGroup(ShaderUniformGroup& group)
{
	_shaderUniformGroups[_currentUniformGroupCount] = group;

	_currentUniformGroupCount++;
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

	_elementList.push_back(newElement);
}

void GPUPipeline::attachOP(GPUPipelineOP op)
{
	_opList.push_back(op);
}

void GPUPipeline::applyState(IGraphicsCommandBlock* commandBlock)
{
	if (_renderShader) {

		auto& constantBuffers = _renderShader->getConstantBuffers();
		for each(DynamicStruct* constBuff in constantBuffers) {

			attachResource(
				constBuff,
				constBuff->getName(),
				0,
				SHADER_RESOURCE_TYPE::CONSTANT_BUFFER,
				constBuff->getTargetShaderType(),
				false
				);

		}
	}


	GraphicsCommandBlock* cmdBlock = (GraphicsCommandBlock*)commandBlock;

	PipelineRenderTargetCommand::InitData::RenderTargetBindInfo rtBindInfo;
	PipelineRenderTargetCommand::InitData::RenderTargetBindInfo rtOpInfo;
	
	std::vector<RenderTarget*> outputRenderTargets;

	cmdBlock->createCommand<PipelineSetPTCommand>
		(&PipelineSetPTCommand::InitData(PRIMITIVE_TOPOLOGY::TRANGLE_LIST));

	for (std::list<GPUPipelineElement>::iterator itr =
		_elementList.begin(); itr != _elementList.end(); ++itr)
	{

		GPUPipelineElement& element = *itr;

		if (element.core != nullptr) {

			if (element.type == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {
				_currentDepthStencil = (DepthStencil*)element.core;
			}

			if (element.type == SHADER_RESOURCE_TYPE::TEXTURE) {

				cmdBlock->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER) {

				cmdBlock->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::CONSTANT_BUFFER) {

				cmdBlock->createCommand<PipelineSRBindCommand>(&PipelineSRBindCommand::InitData
					(element.core, element.bindSlot, element.type, element.parentShader));
			}

			if (element.type == SHADER_RESOURCE_TYPE::GPU_BUFFER) {

				ShaderInputLayout* castIL = (ShaderInputLayout*)_currentInputLayout;

				cmdBlock->createCommand<PipelineBufferBindCommand>(&PipelineBufferBindCommand::InitData
					(std::vector<PipelineBufferBindCommand::InitData::BufferBindInfo>{
					
					PipelineBufferBindCommand::InitData::BufferBindInfo((GPUBuffer*)element.core, 0, castIL->getDataStride())
				
				}));
			}

			if (element.type == SHADER_RESOURCE_TYPE::RENDER_TARGET) {

				if (element.rt_isOutput)
				{
					RenderTarget* realRT = (RenderTarget*)element.core;

					Viewport rtView = realRT->getViewport();
					
					cmdBlock->createCommand<PipelineSetViewportCommand>(&PipelineSetViewportCommand::InitData(rtView));

					outputRenderTargets.push_back((RenderTarget*)element.core);
				}
				else {

					RenderTarget* castRT = (RenderTarget*)element.core;

					rtBindInfo.inputRTList.push_back(PipelineRenderTargetCommand::InitData::InputRenderTargetBindInfo
						(element.bindSlot, element.parentShader, castRT));
				}
			}
		}
	}

	for each(InstanceBufferBindInfo instBuffInfo in _instanceBufferList) {

		std::vector<PipelineBufferBindCommand::InitData::BufferBindInfo> buffersToBind;

		buffersToBind.push_back(PipelineBufferBindCommand::InitData::BufferBindInfo
			((GPUBuffer*)instBuffInfo._vertexBuff, 0, instBuffInfo._vertexBuffStride));

		buffersToBind.push_back(PipelineBufferBindCommand::InitData::BufferBindInfo
			((GPUBuffer*)instBuffInfo._instanceBuff, 0, instBuffInfo._instBuffStride));

		cmdBlock->createCommand<PipelineBufferBindCommand>(&PipelineBufferBindCommand::InitData
			(buffersToBind)
			);
	}

	_instanceBufferList.clear();

	for (int i = 0; i < _currentUniformGroupCount; i++) {
		
		cmdBlock->createCommand<ShaderUpdateUniformCommand>
			(&ShaderUpdateUniformCommand::InitData(_shaderUniformGroups[i], _renderShader));
	}

	_currentUniformGroupCount = 0;

	if (_renderShader) {
		cmdBlock->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(_renderShader));
	}

	if (_currentInputLayout != nullptr) {

		cmdBlock->createCommand<PipelineILBindCommand>(&PipelineILBindCommand::InitData((ShaderInputLayout*)_currentInputLayout));
	}

	cmdBlock->createCommand<PipelineSetBlendStateCommand>(&PipelineSetBlendStateCommand::InitData(blendState));
	cmdBlock->createCommand<PipelineSetDepthTestStateCommand>(&PipelineSetDepthTestStateCommand::InitData(depthState));
	cmdBlock->createCommand<PipelineSetRasterStateCommand>(&PipelineSetRasterStateCommand::InitData((rasterState)));


	for each(RenderTarget* rt in outputRenderTargets) {

		rtBindInfo.outputRTList.push_back(PipelineRenderTargetCommand::InitData::OutputRenderTargetBindInfo
			(_currentDepthStencil, rt));
	}

	cmdBlock->createCommand<PipelineRenderTargetCommand>(&PipelineRenderTargetCommand::InitData(&rtBindInfo));

	if (_renderShader) {
		cmdBlock->createCommand<PipelineBindShaderCommand>(&PipelineBindShaderCommand::InitData(_renderShader));
	}

	switch (_activeDrawMode) {
	case DRAW_MODE::INDEXED:

		cmdBlock->createCommand<PipelineDrawIndexedCommand>
			(&PipelineDrawIndexedCommand::InitData(0, _drawModeIndexedInfo._numIndices));


		break;
	case DRAW_MODE::INSTANCED:

		cmdBlock->createCommand<PipelineDrawInstancedCommand>(&PipelineDrawInstancedCommand::InitData(
			_drawModeInstancedInfo._numIndices, _drawModeInstancedInfo._numInstances));

		break;
	}

	if (_pipelineStateResetAtCompletion) {

		cmdBlock->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());

		_pipelineStateResetAtCompletion = false;
	}

	for (auto itr = _opList.begin(); itr != _opList.end(); itr++) {
		GPUPipelineOP op = *itr;

		if (op.opType == PIPELINE_OP_TYPE::CLEAR) {

			if (op.resType == SHADER_RESOURCE_TYPE::RENDER_TARGET) {

				rtOpInfo.rtOPList.push_back(PipelineRenderTargetCommand::InitData::RendertargetOP
					(RENDER_TARGET_OP_TYPE::CLEAR, (RenderTarget*)op.opTarget));
			}

			if (op.resType == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {

				cmdBlock->createCommand<PipelineClearDepthStencil>
					(&PipelineClearDepthStencil::InitData((DepthStencil*)op.opTarget, 1.0f));
			}
		}

		if (op.opType == PIPELINE_OP_TYPE::SWAPFRAME) {

			cmdBlock->createCommand<PipelineSwapFrame>(&PipelineSwapFrame::InitData());
		}
	}

	cmdBlock->createCommand<PipelineRenderTargetCommand>(&PipelineRenderTargetCommand::InitData(&rtOpInfo));
}
