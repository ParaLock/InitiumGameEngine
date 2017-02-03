#include "../include/GPUPipeline.h"



GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_uniformToBufferMap = new std::map<std::string, DynamicStruct*>;
	_opList = new std::list<GPUPipelineOP*>;
}


GPUPipeline::~GPUPipeline()
{
	delete _elementList;
	delete _uniformToBufferMap;
	delete _opList;
}

void GPUPipeline::reset()
{
	depthTestEnabled = false;
	blendingEnabled = false;

	_uniformToBufferMap->clear();
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


void GPUPipeline::setDepthTest(bool enable)
{
	depthTestEnabled = enable;
}

void GPUPipeline::setBlending(bool enable)
{
	blendingEnabled = enable;
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
			_uniformToBufferMap->insert({ varNameList[i], generalBuff });
		}
	}

	_elementList->insert({ name, newElement });
}
