#pragma once
#include "../../sysInclude.h"

#include "../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../resourceManagerInclude.h"

class EngineInstance
{
private:
	window* _currentWindow;
	GraphicsCore *_graphicsCore;

	ResourceManagerPool* _resManagers;
public:
	EngineInstance(window* renderWindow);
	~EngineInstance();

	void startEngine();

	void stopEngine();

	void loadScene(LPCWSTR sceneFilename);

	GraphicsCore* getGraphicsSubsystem() { return _graphicsCore; };
	ResourceManagerPool* getResourceManagerPool() { return _resManagers; }
};

