#include "../include/GPUPipeline.h"



GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_constantBufferMemberNameMap = new std::map<std::string, DynamicStruct*>;
	_opList = new std::list<GPUPipelineOP*>;
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

	_resManagerPool = realBuilder->_pResManagerPool;

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

		GPUPipelineElementParentShader shaderContext = GPUPipelineElementParentShader::SOL_NON;

		std::string meshDataLayoutContext = "null";
		std::string generalDataContext = "null";

		std::vector<ShaderInputLayout*> inputLayouts;

		for (size_t i = 0; i < line->size(); i++) {

			std::vector<std::string> splitStr = StringManipulation::split(line->at(i), ' ');

			std::string debugTest = splitStr.at(0);

			if (splitStr.at(0) == "VS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "PS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "VS_SHADER_BEGIN") {
				shaderContext = GPUPipelineElementParentShader::SOL_VS;
			}

			if (splitStr.at(0) == "PS_SHADER_BEGIN") {
				shaderContext = GPUPipelineElementParentShader::SOL_PS;
			}

			if (splitStr.at(0) == "INIT") {
				if (splitStr.at(1) == "GBUFFER") {

					realBuilder->_pResManagerPool->getResourceManager("RenderTargetManager")->createResource(
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

					realBuilder->_pResManagerPool->getResourceManager("TextureSamplerManager")->createResource(&TextureSamplerBuilder(
						filterType, ANISOTRPHIC_FILTER_LEVELS::NO_ANISOTROPHIC_FILTERING, addrMode),
						splitStr.at(4), false);
				}
			}


			if (splitStr.at(0) == "BIND") {

				if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "OUTPUT") {


					attachResource(realBuilder->_pResManagerPool->getResourceManager("RenderTargetManager")->getResource(splitStr.at(3)),
						splitStr.at(3), GPUPipelineElementType::SOL_RENDER_TARGET, shaderContext, true);

				}
				else if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "INPUT") {

					attachResource(realBuilder->_pResManagerPool->getResourceManager("RenderTargetManager")->getResource(splitStr.at(3)),
						splitStr.at(3), GPUPipelineElementType::SOL_RENDER_TARGET, shaderContext, false);
				}
				if (splitStr.at(1) == "TEXTURE_HOOK") {

					attachResource(nullptr,
						splitStr.at(2), GPUPipelineElementType::SOL_TEXTURE_HOOK, shaderContext, false);
				}

				if (splitStr.at(1) == "BUFFER_HOOK") {

					attachResource(nullptr,
						splitStr.at(2), GPUPipelineElementType::SOL_BUFFER_HOOK, shaderContext, false);
				}

				if (splitStr.at(1) == "SAMPLER") {

					attachResource(realBuilder->_pResManagerPool->getResourceManager("TextureSamplerManager")->getResource(splitStr.at(2)),
						splitStr.at(2), GPUPipelineElementType::SOL_SAMPLER, shaderContext, false);
				}
			}

			if (splitStr.at(0) == "PIPELINE_OP") {

				bool executionContext;
				GPUPipelineSupportedOP op;
				GPUPipelineElementType opTargetType;

				std::string targetName = "null";

				if (splitStr.at(1) == "DEFERRED") {
					executionContext = true;
				}
				else {
					executionContext = false;
				}

				if (splitStr.at(2) == "CLEAR") {
					op = GPUPipelineSupportedOP::SOL_CLEAR;
				}


				if (splitStr.at(2) == "SWAPFRAME") {

					op = GPUPipelineSupportedOP::SOL_SWAPFRAME;
				}

				if (splitStr.at(3) == "GBUFFER") {

					opTargetType = GPUPipelineElementType::SOL_RENDER_TARGET;
					targetName = splitStr.at(4);
				}

				if (splitStr.at(3) == "ZBUFFER") {
					opTargetType = GPUPipelineElementType::SOL_ZBUFFER;
				}

				attachOP(op, targetName,
					opTargetType, executionContext);
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
	_opList->clear();
	_elementList->clear();
}

void GPUPipeline::attachOP(GPUPipelineSupportedOP opType, std::string targetName, GPUPipelineElementType opTargetType, bool executionContext)
{
	GPUPipelineOP* newOP = new GPUPipelineOP();

	newOP->type = opType;
	newOP->targetType = opTargetType;
	newOP->targetName = targetName;

	_opList->push_back(newOP);
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

void GPUPipeline::attachResource(IResource* res, std::string name, GPUPipelineElementType type,
	GPUPipelineElementParentShader parentShader, bool isOutput)
{
	GPUPipelineElement* newElement = new GPUPipelineElement();

	newElement->isOutput = isOutput;

	newElement->name = name;
	newElement->type = type;
	newElement->parentShader = parentShader;

	newElement->core = res;

	newElement->resourceSlot = 0;

	if (type == GPUPipelineElementType::SOL_RENDER_TARGET) {

		newElement->resourceSlot = renderTargetCount;

		renderTargetCount++;
	}
	if (type == GPUPipelineElementType::SOL_SAMPLER) {

		newElement->resourceSlot = texSamplerCount;

		texSamplerCount++;
	}

	if (type == GPUPipelineElementType::SOL_GENERAL_DATA_BUFF) {

		DynamicStruct* generalBuff = res->getCore<DynamicStruct>();

		std::vector<std::string> varNameList = generalBuff->getVarNameList();

		for (unsigned int i = 0; i < varNameList.size(); ++i) {
			_constantBufferMemberNameMap->insert({ varNameList[i], generalBuff });
		}
	}

	_elementList->insert({ name, newElement });
}
