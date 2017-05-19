#include "../include/Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
	if (_pipelineState != nullptr)
		delete _pipelineState;
}

void Renderer::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_pipelineState = new GPUPipeline();

	_ioInterface = new RenderFlowGraphIOInterface();

	RendererDescriptorParser parser;

	RendererDescriptorData descData = parser.parseRenderDescriptor(realBuilder->_filename);

	_name = descData._rendererName;

	_ioInterface->setParentName(_name);

	ShaderParser shaderParser;

	for each(ShaderToLoad shaderToLoad in descData._shadersToLoad) {
		std::string shaderCode = shaderParser.parseShader(&descData, shaderToLoad._path);

		Shader* newShader = ResourceManagerPool::getInstance()->getResourceManager("ShaderManager")->createResource(std::make_shared<Shader::InitData>
			(shaderCode, true), shaderToLoad._name, false)->getCore<Shader>();

		_shaders.insert({ shaderToLoad._name, newShader });

	}

	for (auto itr = descData._hooksByName.begin(); itr != descData._hooksByName.end(); itr++) {

		RenderFlowGraphNodeIOHook hook = itr->second;
		_ioInterface->addResourceHook(hook);
	}

	DeferredInit();
}

void * Renderer::getParameter(std::string varName)
{
	return nullptr;
}

GPUPipeline * Renderer::rebuildPSO()
{
	//_pipelineState->reset();

	//std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

	//for (auto itr = _shaders.begin(); itr != _shaders.end(); itr++) {
	//	IShader* shader = itr->second;

	//	auto& constantBuffs = shader->getConstantBuffers();

	//	for (auto itr = constantBuffs.begin(); itr != constantBuffs.end(); itr++) {

	//		singleStructs.insert(itr->second);
	//	}
	//}

	//for (auto itr = singleStructs.begin(); itr != singleStructs.end(); itr++) {

	//	std::pair<SHADER_TYPE, DynamicStruct*> data = *itr;

	//	DynamicStruct* buff = data.second;

	//	_pipelineState->attachResource(buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
	//}

	auto& resources = _ioInterface->getLiveHooks();

	for each(RenderFlowGraphNodeIOHook* hook in resources) {

		RendererSpecificIOHookData* specificData = (RendererSpecificIOHookData*)hook->_userData;

		_pipelineState->attachResource(hook->_res, hook->_name, hook->_index,
			specificData->_shaderResType, specificData->_shaderType, hook->_isOutput);
		
	}

	return _pipelineState;
}

