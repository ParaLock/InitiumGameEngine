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

	_resManagers->getResourceManager("InputHandlerManager")->createResource(nullptr, "InputHandler", false);

	_inputHandler = _resManagers->getResourceManager("InputHandlerManager")->
		getResource("InputHandler")->getCore<InputHandler>();

	_graphicsCore = new GraphicsCore(DIRECTX11, renderWindow, _resManagers);

	_currentWindow = renderWindow;
}


EngineInstance::~EngineInstance()
{
	delete _graphicsCore;
	delete _resManagers;
}

void EngineInstance::loadWorld(World * world)
{
	_currentWorld = world;
}

void EngineInstance::executionCycle()
{
	_engineTick.startTimer();

	while (engineActive) {

		update(_engineTick.getElapsedTimeSeconds());

		render();

		if (GetAsyncKeyState(VK_ESCAPE)) {

			stop();

			cleanup();
		}

		_engineTick.reset();
	}
}

void EngineInstance::update(float delta)
{
	const std::map<uint64_t, IEntity*>& worldEntities = _currentWorld->getEntities();

	for (auto itr = worldEntities.begin(); itr != worldEntities.end(); itr++) {
		IEntity* entity = itr->second;


		entity->update(delta);
	}
	
	_inputHandler->update();
}

void EngineInstance::render()
{
	IEntity* cameraEntity = _currentWorld->getEntity(_currentWorld->getPrimaryCameraID());

	_graphicsCore->setCurrentRenderingCamera((CameraComponent*)cameraEntity->getComponentByType(COMPONENT_TYPE::CAMERA_COMPONENT));

	_graphicsCore->render();

	_currentWindow->update();
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
