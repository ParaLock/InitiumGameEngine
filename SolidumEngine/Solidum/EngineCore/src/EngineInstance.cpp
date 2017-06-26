#include "../include/EngineInstance.h"

EngineInstance::EngineInstance(window* renderWindow)
{
	_eventFrameworkCore = new EventFrameworkCore();

	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "ComponentEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "GraphicsEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "InputEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "CameraEventHub");

	_resManagers = new ResourceManagerPool();

	_resManagers->registerResourceManager(new TextureManager(), "TextureManager");
	_resManagers->registerResourceManager(new TextureSamplerManager(), "TextureSamplerManager");
	_resManagers->registerResourceManager(new GPUPipelineManager(), "GPUPipelineManager");
	_resManagers->registerResourceManager(new RenderTargetManager(), "RenderTargetManager");
	_resManagers->registerResourceManager(new ShaderManager(), "ShaderManager");
	_resManagers->registerResourceManager(new MaterialManager(), "MaterialManager");
	_resManagers->registerResourceManager(new meshManager(), "meshManager");
	_resManagers->registerResourceManager(new GPUBufferManager(), "GPUBufferManager");
	_resManagers->registerResourceManager(new LightManager(), "LightManager");
	_resManagers->registerResourceManager(new InputManager(), "InputHandlerManager");
	_resManagers->registerResourceManager(new DepthStencilManager(), "DepthStencilManager");

	_resManagers->getResourceManager("InputHandlerManager")->createResource(nullptr, "InputHandler", false);

	_inputHandler = _resManagers->getResourceManager("InputHandlerManager")->
		getResource("InputHandler")->getCore<InputHandler>();

	_primaryTaskTree = new TaskTree;

	_renderDataCache = new SlabCache(10);

	_graphicsCore = new GraphicsCore(DIRECTX11, renderWindow, _resManagers, _primaryTaskTree);

	_currentWindow = renderWindow;
}


EngineInstance::~EngineInstance()
{
	delete _graphicsCore;
	delete _resManagers;
	delete _renderDataCache;
}

void EngineInstance::engineHeartbeat()
{
	auto& itr = _inflightFrames.begin();

	while (itr != _inflightFrames.end()) {

		Frame& frame = *itr;

		if (frame._renderCMDProcTaskHandle) {

			if (frame._renderCMDProcTaskHandle->_taskComplete == true &&
				frame._simulationTaskHandle->_taskComplete == true &&
				frame._renderPreReqTaskHandle->_taskComplete == true)
			{
				delete frame._scenePipeline;
				delete frame._endScenePipeline;
				delete frame._renderDataGroup;

				if (!_inflightFrames.empty()) {

					itr = _inflightFrames.erase(itr);
				}

				continue;
			}
		}

		if (!_inflightFrames.empty())
			itr++;
	}

	if (_inflightFrames.empty()) {

		GraphicsCommandList* scenePipeline = new GraphicsCommandList();
		GraphicsCommandList* endScenePipeline = new GraphicsCommandList();

		RenderDataGroup* renderDataCollection = new RenderDataGroup(_renderDataCache);

		Frame newFrame;

		newFrame._renderDataGroup = renderDataCollection;

		_inflightFrames.push_back(newFrame);

		Frame& currentFrame = _inflightFrames.back();

		currentFrame._scenePipeline = scenePipeline;
		currentFrame._endScenePipeline = endScenePipeline;

		currentFrame._simulationTaskHandle = _primaryTaskTree->createThreadedTask(
			std::bind(&EngineInstance::update, this, 0.01f, currentFrame._renderDataGroup),
			nullptr, "SimAndRenderThread", false, 1, true);

		currentFrame._renderPreReqTaskHandle = _primaryTaskTree->createThreadedTask(
			std::bind(&GraphicsCore::beginRender, _graphicsCore, std::ref(currentFrame._endScenePipeline), std::ref(currentFrame._scenePipeline), currentFrame._renderDataGroup),
			nullptr, "SimAndRenderThread", false, 1, true);

	}
	else {
		Frame& currentFrame = _inflightFrames.back();

		bool simTask_isComplete = currentFrame._simulationTaskHandle->_taskComplete;
		bool preRenderTask_isComplete = currentFrame._renderPreReqTaskHandle->_taskComplete;

		if (simTask_isComplete && preRenderTask_isComplete) {

			if (!currentFrame._renderCMDProcTaskHandle) {

				currentFrame._renderCMDProcTaskHandle = _primaryTaskTree->createThreadedTask(std::bind(&GraphicsCore::endRender, _graphicsCore, std::ref(currentFrame._endScenePipeline), std::ref(currentFrame._scenePipeline)),
					nullptr, "CommandProcessingThread", false, 1, true);

			}
		}
	}

	IEntity* cameraEntity = _currentWorld->getEntity(_currentWorld->getPrimaryCameraID());

	_graphicsCore->setCurrentRenderingCamera((CameraComponent*)cameraEntity->
		getComponentsByTypeAndIndex(COMPONENT_TYPE::CAMERA_COMPONENT, 0)->front());

}

void EngineInstance::loadWorld(World * world)
{
	_currentWorld = world;
	_graphicsCore->setWorldBoundingSphere(world->getBoundingSphere());
}

void EngineInstance::executionCycle()
{
	while (engineActive) {

		_primaryTaskTree->walk();

		engineHeartbeat();

		if (GetAsyncKeyState(VK_ESCAPE)) {

			stop();
				
			cleanup();
		}
	}
}

void EngineInstance::update(float delta, RenderDataGroup* collection)
{
	const std::map<uint64_t, IEntity*>& worldEntities = _currentWorld->getEntities();

	for (auto itr = worldEntities.begin(); itr != worldEntities.end(); itr++) {
		IEntity* entity = itr->second;

		entity->update(delta, collection);
	}
	
	_inputHandler->update();
}

void EngineInstance::start()
{
	engineActive = true;
	
	executionCycle();
}

void EngineInstance::stop()
{
	engineActive = false;
}

void EngineInstance::cleanup()
{
}
