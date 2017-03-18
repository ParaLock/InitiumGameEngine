#pragma once
#include "../../sysInclude.h"

#include "../../WorldSimulation/include/World.h"

#include "../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../resourceManagerInclude.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

class EngineInstance
{
private:
	HRTimer _engineTick;

	window* _currentWindow;
	GraphicsCore *_graphicsCore;
	ResourceManagerPool* _resManagers;
	EventFrameworkCore* _eventFrameworkCore;
	InputHandler* _inputHandler;

	World* _currentWorld;

	volatile bool engineActive = false;
public:
	EngineInstance(window* renderWindow);
	~EngineInstance();

	void loadWorld(World* world);

	void executionCycle();

	void start();
	void stop();

	void cleanup();

	void update(float delta);
	void render();

	EventFrameworkCore* getEventFrameworkCore() { return _eventFrameworkCore; };
	GraphicsCore* getGraphicsSubsystem() { return _graphicsCore; };
	ResourceManagerPool* getResourceManagerPool() { return _resManagers; }
};

