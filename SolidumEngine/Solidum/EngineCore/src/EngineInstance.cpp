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

	_resManagers->getResourceManager("InputHandlerManager")->createResource(nullptr, "InputHandler");

	_graphicsCore = new GraphicsCore(DIRECTX11, renderWindow, _resManagers);
}


EngineInstance::~EngineInstance()
{
	delete _graphicsCore;
	delete _resManagers;
}

void EngineInstance::startEngine()
{
}

void EngineInstance::stopEngine()
{
}
