#pragma once
#include "../../../sysInclude.h"

#include "RenderPass.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"
#include "../../../ResourceFramework/include/IResource.h"

#include "../../RenderDataStream/include/RenderDataBatch.h"
#include "../../RenderDataStream/include/RenderDataStream.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

enum PASS_TYPE {
	MESH_PASS,
	LIGHT_PASS,
	FX_PASS
};

class RenderProcessBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	ResourceManagerPool* _resManagerPool;

	RenderProcessBuilder(LPCWSTR filename, ResourceManagerPool* resManagerPool) {
		_filename = filename;
		_resManagerPool = resManagerPool;
	}
};

class RenderProcess : public IResource
{
private:
	std::list<RenderDataStream*> *_registeredStreams;

	std::list<RenderPass> *_passes;

	ResourceManagerPool* _resManagerPool;

public:
	RenderProcess();
	~RenderProcess();

	void load(IResourceBuilder* builder);
	void unload();

	void registerDataStream(RenderDataStream* stream);

	std::list<RenderDataStream*>* getRegisteredStreams() { return _registeredStreams; }

	void execute();
};

