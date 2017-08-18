#include "../include/EngineInstance.h"

EngineInstance::EngineInstance(window* renderWindow)
{
	_resourceCreator = new ResourceCreator(this);

	_eventFrameworkCore = new EventFrameworkCore();

	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "ComponentEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "GraphicsEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "InputEventHub");
	_eventFrameworkCore->registerGlobalEventHub(new EventHub(), "CameraEventHub");

	_inputHandler = _resourceCreator->createResourceImmediate<InputHandler>(&InputHandler::InitData(), "core_input_handler", [](IResource*) {});

	_primaryTaskTree = new TaskTree(*_resourceCreator);

	_renderDataCache = new SlabCache();

	_graphicsCore = new GraphicsCore(DIRECTX11, renderWindow, _primaryTaskTree, *_resourceCreator, this);

	_currentWindow = renderWindow;

	//auto resourceCreationTaskHandle = _primaryTaskTree->createThreadedTask(
	//	std::bind(&ResourceCreator::loadPendingResources, _resourceCreator),
	//	nullptr, "ResourceCreationThread", true, 1, true);

	//_resourceCreator->setTaskHandle(resourceCreationTaskHandle);
}


EngineInstance::~EngineInstance()
{
	delete _graphicsCore;
	delete _renderDataCache;

	delete _resourceCreator;
}

ResourceLookupCache * EngineInstance::getResourceLookupCache(std::string & resourceGroup)
{
	auto& itr = _ResourceLookupCacheByGroupName.find(resourceGroup);

	if (itr != _ResourceLookupCacheByGroupName.end()) {

		return _ResourceLookupCacheByGroupName.at(resourceGroup);

	}
	else {

		ResourceLookupCache* newCache = new ResourceLookupCache();

		_ResourceLookupCacheByGroupName.insert({ resourceGroup, newCache });

		return newCache;
	}
}

void EngineInstance::engineHeartbeat()
{
	Entity* cameraEntity = (Entity*)_currentWorld->getEntity(_currentWorld->getPrimaryCameraID());

	CameraComponent* cameraComponent = cameraEntity->getComponent<CameraComponent>(0);

	_graphicsCore->setCurrentRenderingCamera(cameraComponent);

	//auto& itr = _inflightFrames.begin();

	//while (itr != _inflightFrames.end()) {

	//	Frame& frame = *itr;

	//	if (frame._renderCMDProcTaskHandle) {

	//		if (frame._renderCMDProcTaskHandle->_taskComplete == true &&
	//			frame._simulationTaskHandle->_taskComplete == true &&
	//			frame._renderPreReqTaskHandle->_taskComplete == true)
	//		{
	//			delete frame._scenePipeline;
	//			delete frame._endScenePipeline;

	//			frame._renderDataGroup->freeRenderPackets();

	//			delete frame._renderDataGroup;

	//			if (!_inflightFrames.empty()) {

	//				itr = _inflightFrames.erase(itr);
	//			}

	//			continue;
	//		}
	//	}

	//	if (!_inflightFrames.empty())
	//		itr++;
	//}

	//if (_inflightFrames.empty()) {

		GraphicsCommandList* scenePipeline = new GraphicsCommandList(_resourceCreator);
		GraphicsCommandList* endScenePipeline = new GraphicsCommandList(_resourceCreator);

		RenderDataGroup* renderDataCollection = new RenderDataGroup(_renderDataCache);

	//	Frame newFrame;

	//	newFrame._renderDataGroup = renderDataCollection;

	//	_inflightFrames.push_back(newFrame);

	//	Frame& currentFrame = _inflightFrames.back();

	//	currentFrame._scenePipeline = scenePipeline;
	//	currentFrame._endScenePipeline = endScenePipeline;

	//	currentFrame._simulationTaskHandle = _primaryTaskTree->createThreadedTask(

	//		std::bind(&EngineInstance::update, this, 0.01f,
	//		currentFrame._renderDataGroup),
	//		nullptr, "SimAndRenderThread", false, 1, true);

	//	currentFrame._renderPreReqTaskHandle = _primaryTaskTree->createThreadedTask(

	//		std::bind(&GraphicsCore::beginRender, _graphicsCore, 
	//		std::ref(currentFrame._endScenePipeline), 
	//		std::ref(currentFrame._scenePipeline), 
	//		currentFrame._renderDataGroup),
	//		nullptr, "SimAndRenderThread", false, 1, true);

	//}
	//else {
	//	Frame& currentFrame = _inflightFrames.back();

	//	bool simTask_isComplete = currentFrame._simulationTaskHandle->_taskComplete;
	//	bool preRenderTask_isComplete = currentFrame._renderPreReqTaskHandle->_taskComplete;

	//	if (simTask_isComplete && preRenderTask_isComplete) {

	//		if (!currentFrame._renderCMDProcTaskHandle) {

	//			currentFrame._renderCMDProcTaskHandle = _primaryTaskTree->createThreadedTask(

	//				std::bind(&GraphicsCore::endRender, _graphicsCore, 
	//				std::ref(currentFrame._endScenePipeline), 
	//				std::ref(currentFrame._scenePipeline)),
	//				nullptr, "CommandProcessingThread", false, 1, true);

	//		}
	//	}
	//}

		PerfProfiler profiler;

		profiler.start();

		update(0.004, renderDataCollection);
		
		profiler.end("Engine Update Complete: ");

		profiler.start();

		_graphicsCore->beginRender(endScenePipeline, scenePipeline, renderDataCollection);
		
		profiler.end("BegineRender Complete: ");
		
		profiler.start();

		_graphicsCore->endRender(endScenePipeline, scenePipeline);

		profiler.end("EndRender Complete: ");

		renderDataCollection->freeRenderPackets();

		delete scenePipeline;
		delete endScenePipeline;
		delete renderDataCollection;
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
