#pragma once
#include "../../sysInclude.h"

#include "../../WorldSimulation/include/World.h"

#include "../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../GraphicsRendering/Window/include/window.h"

#include "../../EventFramework/include/EventFrameworkCore.h"

#include "../../MemoryManagement/include/SlabCache.h"

#include "../../TaskFramework/include/TaskTree.h"

#include "../../ResourceFramework/include/ResourceCreator.h"

#include "../../ResourceFramework/include/ResourceLookupCache.h"

#include "IEngineInstance.h"

class EngineInstance : public IEngineInstance
{
private:

	const static int MAX_PRE_RENDERED_FRAMES = 3;

	struct Frame {

		GraphicsCommandList* _endScenePipeline;
		GraphicsCommandList* _scenePipeline;

		RenderDataGroup* _renderDataGroup;

		std::shared_ptr<TaskHandle> _renderPreReqTaskHandle;
		std::shared_ptr<TaskHandle> _simulationTaskHandle;
		std::shared_ptr<TaskHandle> _renderCMDProcTaskHandle;
	};

	ResourceCreator* _resourceCreator;

	std::list<Frame> _inflightFrames;

	HRTimer _engineTick;

	SlabCache* _renderDataCache;

	window* _currentWindow;
	GraphicsCore *_graphicsCore;
	EventFrameworkCore* _eventFrameworkCore;
	InputHandler* _inputHandler;

	World* _currentWorld;

	TaskTree* _primaryTaskTree;

	volatile bool engineActive = false;

	std::map<std::string, ResourceLookupCache*> _ResourceLookupCacheByGroupName;
public:
	EngineInstance(window* renderWindow);
	~EngineInstance();

	ResourceLookupCache* getResourceLookupCache(std::string& resourceGroup);

	void engineHeartbeat();

	void loadWorld(World* world);

	void executionCycle();

	void start();
	void stop();

	void cleanup();

	void update(float delta, RenderDataGroup* collection);

	ResourceCreator& getResourceCreator() { return *_resourceCreator; };

	World* getWorld() { return _currentWorld; }

	EventFrameworkCore* getEventFrameworkCore() { return _eventFrameworkCore; };
	GraphicsCore* getGraphicsSubsystem() { return _graphicsCore; };
};

