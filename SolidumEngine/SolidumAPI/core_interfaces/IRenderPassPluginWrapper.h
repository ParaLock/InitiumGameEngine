#pragma once

class IGPUPipeline;
class IShader;
class IRenderFlowGraphIOInterface;
class IResourceCreator;
class SlabCache;
class IRenderDataGroup;
class IGraphicsCommandBlock;

class IRenderPassPluginWrapper {
public:
	virtual SlabCache& getCache() = 0;

	virtual IRenderFlowGraphIOInterface* getIOInterface() = 0;

	virtual IShader* getShader(std::string& name) = 0;
	virtual IGPUPipeline* getPSO() = 0;

	virtual void rebuildPSO(IGPUPipeline* pso) = 0;

	virtual void execute(
		IRenderDataGroup * collection,
		IGraphicsCommandBlock * commandBlock) = 0;
};