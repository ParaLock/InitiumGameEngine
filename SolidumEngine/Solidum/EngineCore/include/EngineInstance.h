#pragma once
#include "../../sysInclude.h"

#include "../../WorldSimulation/include/World.h"

#include "../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../resourceManagerInclude.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../TaskFramework/include/TaskTree.h"

class EngineInstance
{
private:

	const static int MAX_PRE_RENDERED_FRAMES = 3;

	struct FrameTasks {

		GraphicsCommandList* _endScenePipeline;
		GraphicsCommandList* _scenePipeline;

		std::shared_ptr<TaskHandle> _renderPreReqTaskHandle;
		std::shared_ptr<TaskHandle> _simulationTaskHandle;
		std::shared_ptr<TaskHandle> _renderCMDProcTaskHandle;
	};

	std::list<FrameTasks> _inflightFrames;

	HRTimer _engineTick;

	window* _currentWindow;
	GraphicsCore *_graphicsCore;
	ResourceManagerPool* _resManagers;
	EventFrameworkCore* _eventFrameworkCore;
	InputHandler* _inputHandler;

	World* _currentWorld;

	TaskTree* _primaryTaskTree;

	volatile bool engineActive = false;
public:
	EngineInstance(window* renderWindow);
	~EngineInstance();

	void engineHeartbeat();

	void loadWorld(World* world);

	void executionCycle();

	void start();
	void stop();

	void cleanup();

	std::shared_ptr<TaskHandle> testTaskHandle;

	void update(float delta);

	World* getWorld() { return _currentWorld; }

	EventFrameworkCore* getEventFrameworkCore() { return _eventFrameworkCore; };
	GraphicsCore* getGraphicsSubsystem() { return _graphicsCore; };
	ResourceManagerPool* getResourceManagerPool() { return _resManagers; }
};

