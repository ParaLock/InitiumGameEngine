#include "../include/GPUPipeline.h"


GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_opList = new std::list<GPUPipelineOP>;
}


GPUPipeline::~GPUPipeline()
{
	delete _elementList;
	delete _opList;
}

void GPUPipeline::load(std::shared_ptr<IResourceBuilder> builder)
{
	isLoaded = true;
}

void GPUPipeline::unload()
{
	isLoaded = false;
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
	GPUPipelineElement* newElement = new GPUPipelineElement();

	newElement->rt_isOutput = isOutput;

	newElement->type = type;
	newElement->parentShader = parentShader;

	newElement->core = res;

	newElement->bindSlot = index;

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachOP(GPUPipelineOP op)
{
	_opList->push_back(op);
}

void GPUPipeline::applyState(GraphicsCommandList* commandList)
{
	std::list<RenderTarget*> outputRTs;

	commandList->createCommand(std::make_shared<PipelineSetPTCommand::InitData>(PRIMITIVE_TOPOLOGY::TRANGLE_LIST), 
		GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_PRIMITIVE_TOPOLOGY);

	for (std::map<std::string, GPUPipelineElement*>::iterator itr =
		_elementList->begin(); itr != _elementList->end(); ++itr)
	{

		GPUPipelineElement* element = itr->second;

		if (element->core != nullptr) {

			if (element->type == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {
				_currentDepthStencil = element->core->getCore<DepthStencil>();
			}

			if (element->type == SHADER_RESOURCE_TYPE::TEXTURE) {

				commandList->createCommand(std::make_shared<PipelineSRBindCommand::InitData>
					(element->core, element->bindSlot, element->type, element->parentShader), 
					  GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SR);
			}

			if (element->type == SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER) {

				commandList->createCommand(std::make_shared<PipelineSRBindCommand::InitData>
					(element->core, element->bindSlot, element->type, element->parentShader), 
					  GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SR);
			}

			if (element->type == SHADER_RESOURCE_TYPE::CONSTANT_BUFFER) {

				commandList->createCommand(std::make_shared<PipelineSRBindCommand::InitData>
					(element->core, element->bindSlot, element->type, element->parentShader), 
					  GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_SR);
			}

			if (element->type == SHADER_RESOURCE_TYPE::GPU_BUFFER) {

				commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
					(std::vector<GPUBuffer*> {element->core->getCore<GPUBuffer>()}, 
					 std::vector<UINT> {0}, 
					 std::vector<UINT>{_currentInputLayout->getCore<ShaderInputLayout>()->getDataStride()}),
					
					 GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER);

			}

			if (element->type == SHADER_RESOURCE_TYPE::RENDER_TARGET) {
				if (element->rt_isOutput)
				{
					outputRTs.push_back((RenderTarget*)element->core);

					Viewport rtView = element->core->getCore<RenderTarget>()->getViewport();
					
					commandList->createCommand(std::make_shared<PipelineSetViewportCommand::InitData>
						(rtView), GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VIEWPORT_STATE);
				}
				else {

					commandList->createCommand(std::make_shared<PipelineRenderTargetCommand::InitData>
						  (element->bindSlot, element->parentShader, 
							std::list<RenderTarget*>{ (RenderTarget*)element->core }, 
							 RENDER_TARGET_OP_TYPE::BIND_AS_INPUT,
							  _currentDepthStencil),
				     GRAPHICS_COMMAND_TYPE::PIPELINE_RENDER_TARGET_COMMAND);
					
				}
			}
		}
	}

	if (_currentInputLayout != nullptr) {

		commandList->createCommand(std::make_shared<PipelineILBindCommand::InitData>(_currentInputLayout), 
			GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_INPUT_LAYOUT);
	}

	commandList->createCommand(std::make_shared<PipelineRenderTargetCommand::InitData>
		(-1, SHADER_TYPE::INVALID_ST, outputRTs, RENDER_TARGET_OP_TYPE::BIND_AS_OUTPUT, 
			_currentDepthStencil),
			GRAPHICS_COMMAND_TYPE::PIPELINE_RENDER_TARGET_COMMAND);

	commandList->createCommand(std::make_shared<PipelineSetBlendStateCommand::InitData>(blendState), GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_BLEND_STATE);
	commandList->createCommand(std::make_shared<PipelineSetDepthTestStateCommand::InitData>(depthState), GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_DEPTH_TEST_STATE);
	commandList->createCommand(std::make_shared<PipelineSetRasterStateCommand::InitData>((rasterState)), GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_RASTER_STATE);

	for (auto itr = _opList->begin(); itr != _opList->end(); itr++) {
		GPUPipelineOP op = *itr;
		
		if (op.opType == PIPELINE_OP_TYPE::CLEAR) {

			if (op.resType == SHADER_RESOURCE_TYPE::RENDER_TARGET) {

				commandList->createCommand(std::make_shared<PipelineRenderTargetCommand::InitData>
					(-1, SHADER_TYPE::INVALID_ST, std::list<RenderTarget*>{(RenderTarget*)op.opTarget},
						RENDER_TARGET_OP_TYPE::CLEAR, nullptr), GRAPHICS_COMMAND_TYPE::PIPELINE_RENDER_TARGET_COMMAND);
			}
		
			if (op.resType == SHADER_RESOURCE_TYPE::DEPTH_STENCIL) {
				
				commandList->createCommand(std::make_shared<PipelineClearDepthStencil::InitData>((DepthStencil*)op.opTarget, 1.0f), 
				    GRAPHICS_COMMAND_TYPE::PIPELINE_CLEAR_DEPTH_BUFFER);
			}
		}

		if (op.opType == PIPELINE_OP_TYPE::SWAPFRAME) {

			commandList->createCommand(std::make_shared<IResourceBuilder>(), 
				GRAPHICS_COMMAND_TYPE::PIPELINE_SWAPFRAME);
		}
	}
}
