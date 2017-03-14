#include "../include/GPUPipeline.h"



GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_constantBufferMemberNameMap = new std::map<std::string, DynamicStruct*>;
	_opList = new std::list<GPUPipelineOP>;
}


GPUPipeline::~GPUPipeline()
{
	delete _elementList;
	delete _constantBufferMemberNameMap;
	delete _opList;
}

void GPUPipeline::load(IResourceBuilder * builder)
{
	GPUPipelineBuilder* realBuilder = static_cast<GPUPipelineBuilder*>(builder);

	std::wstring filePathWStr(realBuilder->_filename);

	std::string filepathSTLStr = StringManipulation::ws2s(filePathWStr);

	std::ifstream file(realBuilder->_filename);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("Pipeline descriptor file open failed!\n");
	}
	else {
		char buf[256];

		while (!file.eof())
		{
			file.getline(buf, 256);

			if (buf[0] != 0)
				line->push_back(new std::string(buf));
		}

		SHADER_TYPE shaderContext = SHADER_TYPE::INVALID;

		std::string meshDataLayoutContext = "null";
		std::string generalDataContext = "null";

		std::vector<ShaderInputLayout*> inputLayouts;

		for (size_t i = 0; i < line->size(); i++) {

			std::vector<std::string> splitStr = StringManipulation::split(line->at(i), ' ');

			std::string debugTest = splitStr.at(0);

			if (splitStr.at(0) == "VS_SHADER_END") {
				shaderContext = SHADER_TYPE::INVALID;
			}

			if (splitStr.at(0) == "PS_SHADER_END") {
				shaderContext = SHADER_TYPE::INVALID;
			}

			if (splitStr.at(0) == "VS_SHADER_BEGIN") {
				shaderContext = SHADER_TYPE::VERTEX_SHADER;
			}

			if (splitStr.at(0) == "PS_SHADER_BEGIN") {
				shaderContext = SHADER_TYPE::PIXEL_SHADER;
			}

			if (splitStr.at(0) == "INIT") {
				if (splitStr.at(1) == "GBUFFER") {

					ResourceManagerPool::getInstance()->getResourceManager("RenderTargetManager")->createResource(
						&RenderTargetBuilder(1, 1, TEX_FORMAT::RGBA_32BIT_FLOAT), splitStr.at(2), false);
				}

				if (splitStr.at(1) == "SAMPLER") {
					TEX_ADDR_MODES addrMode;
					TEX_FILTERS filterType;

					if (splitStr.at(2) == "WRAP") {
						addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_WRAP;
					}
					if (splitStr.at(2) == "CLAMP") {
						addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_CLAMP;
					}

					if (splitStr.at(3) == "LINEAR") {
						filterType = TEX_FILTERS::TEX_FILTER_LINEAR;
					}

					if (splitStr.at(3) == "POINT") {
						filterType = TEX_FILTERS::TEX_FILTER_POINT;
					}

					ResourceManagerPool::getInstance()->getResourceManager("TextureSamplerManager")->createResource(&TextureSamplerBuilder(
						filterType, ANISOTRPHIC_FILTER_LEVELS::NO_ANISOTROPHIC_FILTERING, addrMode),
						splitStr.at(4), false);
				}
			}


			if (splitStr.at(0) == "BIND") {

				if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "OUTPUT") {

					IResource* res = ResourceManagerPool::getInstance()->getResourceManager("RenderTargetManager")->getResource(splitStr.at(3));

					attachResource(res,
						splitStr.at(3), SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET, shaderContext, true);

				}
				else if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "INPUT") {

					IResource* res = ResourceManagerPool::getInstance()->getResourceManager("RenderTargetManager")->getResource(splitStr.at(3));

					attachResource(res,
						splitStr.at(3), SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET, shaderContext, false);
				}
				if (splitStr.at(1) == "TEXTURE_HOOK") {

					attachResource(nullptr,
						splitStr.at(2), SHADER_RESOURCE_TYPE::SHADER_TEXTURE_HOOK, shaderContext, false);
				}

				if (splitStr.at(1) == "BUFFER_HOOK") {

					attachResource(nullptr,
						splitStr.at(2), SHADER_RESOURCE_TYPE::SHADER_BUFFER_HOOK, shaderContext, false);
				}

				if (splitStr.at(1) == "SAMPLER") {

					attachResource(ResourceManagerPool::getInstance()->getResourceManager("TextureSamplerManager")->getResource(splitStr.at(2)),
						splitStr.at(2), SHADER_RESOURCE_TYPE::SHADER_TEX_SAMPLER, shaderContext, false);
				}
			}

			if (splitStr.at(0) == "PIPELINE_OP") {

				GPUPipelineOP op;

				bool executionContext;

				if (splitStr.at(1) == "DEFERRED") {
					executionContext = true;
				}
				else {
					executionContext = false;
				}

				if (splitStr.at(2) == "CLEAR") {

					op.opType = GPUPIPELINE_OP_TYPE::CLEAR;
				}

				if (splitStr.at(2) == "SWAPFRAME") {
					op.opType = GPUPIPELINE_OP_TYPE::SWAPFRAME;
				}

				if (splitStr.at(3) == "GBUFFER") {

					op.resType = SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET;

					op.opTarget = ResourceManagerPool::getInstance()->getResourceManager("RenderTargetManager")->getResource(splitStr.at(4));
				}

				if (splitStr.at(3) == "ZBUFFER") {
					op.resType = SHADER_RESOURCE_TYPE::SHADER_ZBUFFER;
				}


				attachOP(op);
			}

			if (splitStr.at(0) == "DEPTH_TEST") {

				if (splitStr.at(1) == "enable") {
					setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
				}
				else {
					setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
				}
			}

			if (splitStr.at(0) == "BLENDING") {
				if (splitStr.at(1) == "enable") {

					blendState = BLEND_STATE::LIGHT_BLENDING;
				}
				else {
					blendState = BLEND_STATE::BLENDING_OFF;
				}
			}
		}
	}

	isLoaded = true;
}

void GPUPipeline::unload()
{
	isLoaded = false;
}

void GPUPipeline::reset()
{
	blendState = BLEND_STATE::BLENDING_OFF;

	_constantBufferMemberNameMap->clear();
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

void GPUPipeline::setHookResource(IResource* res, std::string name)
{
	auto itr = _elementList->find(name);

	if (itr != _elementList->end()) {

		GPUPipelineElement* pipeElement = _elementList->at(name);

		pipeElement->core = res;
	}
}

void GPUPipeline::attachResource(IResource* res, std::string name, SHADER_RESOURCE_TYPE type,
	SHADER_TYPE parentShader, bool isOutput)
{
	GPUPipelineElement* newElement = new GPUPipelineElement();

	newElement->isOutput = isOutput;

	newElement->type = type;
	newElement->parentShader = parentShader;

	newElement->core = res;

	newElement->bindSlot = 0;

	if (type == SHADER_RESOURCE_TYPE::SHADER_TEXTURE_HOOK) {

		newElement->bindSlot = texHookCount;

		texHookCount++;
	}

	if (type == SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET) {

		newElement->bindSlot = renderTargetCount;

		renderTargetCount++;
	}
	if (type == SHADER_RESOURCE_TYPE::SHADER_TEX_SAMPLER) {

		newElement->bindSlot = texSamplerCount;

		texSamplerCount++;
	}

	if (type == SHADER_RESOURCE_TYPE::SHADER_CONSTANT_BUFFER) {

		DynamicStruct* generalBuff = res->getCore<DynamicStruct>();

		std::vector<std::string> varNameList = generalBuff->getVarNameList();

		for (unsigned int i = 0; i < varNameList.size(); ++i) {
			_constantBufferMemberNameMap->insert({ varNameList[i], generalBuff });
		}
	}

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachOP(GPUPipelineOP op)
{
	_opList->push_back(op);
}

void GPUPipeline::applyState()
{
	std::list<IResource*> outputRTs;

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new PipelineSetPTCommand(PRIMITIVE_TOPOLOGY::TRANGLE_LIST));

	for (std::map<std::string, GPUPipelineElement*>::iterator itr =
		_elementList->begin(); itr != _elementList->end(); ++itr)
	{

		GPUPipelineElement* element = itr->second;

		if (element->core != nullptr) {

			if (element->type == SHADER_RESOURCE_TYPE::SHADER_TEXTURE_HOOK) {

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSRBindCommand(element->bindSlot, element->core, element->parentShader, element->type));
			}

			if (element->type == SHADER_RESOURCE_TYPE::SHADER_TEX_SAMPLER) {

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSRBindCommand(element->bindSlot, element->core, element->parentShader, element->type));
			}

			if (element->type == SHADER_RESOURCE_TYPE::SHADER_CONSTANT_BUFFER) {

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSRBindCommand(element->bindSlot, element->core, element->parentShader, element->type));
			}

			if (element->type == SHADER_RESOURCE_TYPE::SHADER_BUFFER_HOOK) {

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineBufferBindCommand(element->core, 0, 
						_currentInputLayout->getCore<ShaderInputLayout>()->getDataStride()));

			}

			if (element->type == SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET) {
				if (element->isOutput)
				{
					outputRTs.push_back(element->core);
				}
				else {
					GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
						new PipelineRenderTargetCommand(RENDER_TARGET_OP_TYPE::BIND_AS_INPUT,
							element->parentShader, element->bindSlot, std::list<IResource*>{ element->core }));
				}
			}
		}
	}

	if (_currentInputLayout != nullptr)
		GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineILBindCommand(_currentInputLayout));
	

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineRenderTargetCommand(RENDER_TARGET_OP_TYPE::BIND_AS_OUTPUT,
		SHADER_TYPE::INVALID, -1, outputRTs));

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineSetBlendStateCommand(blendState));
	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineSetDepthTestStateCommand(depthState));
	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineSetRasterStateCommand(rasterState));

	for (auto itr = _opList->begin(); itr != _opList->end(); itr++) {
		GPUPipelineOP op = *itr;
		
		if (op.opType == GPUPIPELINE_OP_TYPE::CLEAR) {

			if(op.resType == SHADER_RESOURCE_TYPE::SHADER_RENDER_TARGET)
				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineRenderTargetCommand(RENDER_TARGET_OP_TYPE::CLEAR, SHADER_TYPE::INVALID, -1, std::list<IResource*>{op.opTarget}));
		
			if (op.resType == SHADER_RESOURCE_TYPE::SHADER_ZBUFFER)
				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineClearDepthStencil());
		}

		if (op.opType == GPUPIPELINE_OP_TYPE::SWAPFRAME) {
			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(new PipelineSwapFrame());
		}
	}
}
