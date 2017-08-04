#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../GPUPipeline/include/GPUPipeline.h"
#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/EventHub.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "RenderFlowGraphIOInterface.h"

#include "RenderFlowGraphParser.h"

struct NodeExecuteData {
	std::string _nodeCoreName;
	std::string _nodeCoreManagerName;
};

class ResourcePool;

class RenderFlowGraph : public IEventListener, public Resource<RenderFlowGraph, GenericFactory, ResourcePool>
{
private:
	std::string _name;

	virtual void unload() {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	std::map<std::string, std::string> _resourceGroupByType;

	std::map<std::string, RenderFlowGraphIOInterface*> _registeredIOInterfaces;

	std::list<std::string> _orderedNodeNames;
public:
	RenderFlowGraph();
	~RenderFlowGraph();

	static const unsigned int TYPE = 0;

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		std::string _filename;

		ResourceCreator* _resCreator;

		InitData(std::string descFilename, ResourceCreator* resCreator) :
			_filename(descFilename),
			_resCreator(resCreator)
		{

		}
	};

	void registerIOInterface(RenderFlowGraphIOInterface* ioInterface);

	void load();

	std::list<std::string> getNodeExecutionOrder();

	void onEvent(EVENT_PTR evt);

protected:
};

