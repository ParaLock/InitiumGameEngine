#pragma once
#include "../../sysInclude.h"

#include "../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../resourceManagerInclude.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

class EngineInstance
{
private:
	window* _currentWindow;
	GraphicsCore *_graphicsCore;
	ResourceManagerPool* _resManagers;
	EventFrameworkCore* _eventFrameworkCore;
public:
	EngineInstance(window* renderWindow);
	~EngineInstance();

	void startEngine();

	void stopEngine();

	EventFrameworkCore* getEventFrameworkCore() { return _eventFrameworkCore; };
	GraphicsCore* getGraphicsSubsystem() { return _graphicsCore; };
	ResourceManagerPool* getResourceManagerPool() { return _resManagers; }
};

