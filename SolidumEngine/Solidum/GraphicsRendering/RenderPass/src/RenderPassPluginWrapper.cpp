#include "../include/RenderPassPluginWrapper.h"



RenderPassPluginWrapper::RenderPassPluginWrapper()
{
}


RenderPassPluginWrapper::~RenderPassPluginWrapper()
{
}

void RenderPassPluginWrapper::unload()
{
}

void RenderPassPluginWrapper::execute(IRenderDataGroup * collection, IGraphicsCommandBlock * commandBlock)
{
	_pluginInterface->execute(collection, commandBlock, this);
}

void RenderPassPluginWrapper::rebuildPSO(IGPUPipeline* pso)
{
	GPUPipeline* castPSO = dynamic_cast<GPUPipeline*>(pso);

	auto& resources = _ioInterface->getLiveHooks();

	for each(RenderFlowGraphNodeIOHook* hook in resources) {

		RenderPassSpecificIOHookData* specificData = (RenderPassSpecificIOHookData*)hook->_userData;

		castPSO->attachResource(hook->_res, hook->_name, hook->_index,
			specificData->_shaderResType, specificData->_shaderType, hook->_isOutput);

	}

}

void RenderPassPluginWrapper::load()
{
	InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

	_ioInterface = new RenderFlowGraphIOInterface();

	RenderPassDescriptorParser parser;

	RenderPassDescriptorData descData = parser.parseRenderPassDescriptor(realBuilder->_filename);

	_name = descData._renderPassName;

	name(_name);

	_ioInterface->setParentName(_name);

	ShaderParser shaderParser;

	for each(ShaderToLoad shaderToLoad in descData._shadersToLoad) {

		std::string shaderCode = shaderParser.parseShader(&descData, shaderToLoad._path);

		Shader* newShader = (Shader*)realBuilder->_resourceCreator->createResourceImmediate<Shader>(&Shader::InitData(&shaderCode, true, realBuilder->_resourceCreator), shaderToLoad._name,
			[=](IResource* res) {ResourceUtils::addResourceToGroup(res, std::string("ShaderGroup"), realBuilder->_resourceCreator->getParentEngine()); });

		newShader->updateGPU();

		_shaders.insert({ shaderToLoad._name, newShader });

	}

	for (auto itr = descData._hooksByName.begin(); itr != descData._hooksByName.end(); itr++) {

		RenderFlowGraphNodeIOHook hook = itr->second;
		_ioInterface->addResourceHook(hook);
	}
}
