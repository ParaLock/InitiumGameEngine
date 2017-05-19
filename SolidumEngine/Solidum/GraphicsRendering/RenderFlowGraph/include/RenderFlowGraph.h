#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../GPUPipeline/include/GPUPipeline.h"
#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/EventHub.h"

#include "RenderFlowGraphIOInterface.h"

#include "RenderFlowGraphParser.h"

struct NodeExecuteData {
	std::string _nodeCoreName;
	std::string _nodeCoreManagerName;
};

class RenderFlowGraph : public IEventListener, public IResource
{
private:
	std::string _name;

	virtual void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::map<std::string, std::string> _managerNameByResourceTypeName;

	std::map<std::string, RenderFlowGraphIOInterface*> _registeredIOInterfaces;

	std::list<std::string> _orderedNodeNames;
public:
	RenderFlowGraph();
	~RenderFlowGraph();

	struct InitData : public IResourceBuilder {

		std::string _filename;

		InitData(std::string descFilename) :
			_filename(descFilename)
		{

		}
	};

	void registerIOInterface(RenderFlowGraphIOInterface* ioInterface);

	void load(std::shared_ptr<IResourceBuilder> builder);

	std::list<std::string> getNodeExecutionOrder();

	void onEvent(EVENT_PTR evt);
};

