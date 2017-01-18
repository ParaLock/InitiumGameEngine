#include "../include/EngineInstance.h"



EngineInstance::EngineInstance(window* renderWindow)
{
	_resManagers = new ResourceManagerPool();

	_resManagers->registerResourceManager(new TextureManager(), "TextureManager");
	_resManagers->registerResourceManager(new TextureSamplerManager(), "TextureSamplerManager");
	_resManagers->registerResourceManager(new GPUPipelineManager(), "GPUPipelineManager");
	_resManagers->registerResourceManager(new RenderTargetManager(), "RenderTargetManager");
	_resManagers->registerResourceManager(new ShaderManager(), "ShaderManager");
	_resManagers->registerResourceManager(new MaterialManager(), "MaterialManager");
	_resManagers->registerResourceManager(new meshManager(), "meshManager");
	_resManagers->registerResourceManager(new GPUBufferManager(), "GPUBufferManager");
	_resManagers->registerResourceManager(new SolidumObjectManager(), "SolidumObjectManager");
	_resManagers->registerResourceManager(new LightManager(), "LightManager");

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

void EngineInstance::loadScene(LPCWSTR sceneFilename)
{
}
