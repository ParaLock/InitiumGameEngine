#pragma once
#include "../../../sysInclude.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/TextureSampler.h"

#include "../../Window/include/window.h"

struct ParsedNodeEdge {
	std::string _name;
	std::string _type;

	int _index;

	bool _isOutput;
};

struct ParsedRenderFlowGraphOP {
	std::string _opType;
	std::string _targetName;
	std::string _targetType;
};

struct ParsedNodeData {
	std::string _name;

	std::string _coreName;

	std::list<ParsedNodeEdge> _edges;
};

struct ParsedRenderFlowGraphData {
	std::string _graphName;

	std::list<std::string> _orderedNodeNames;

	std::list<ParsedNodeData> _nodes;

	std::list<ParsedRenderFlowGraphOP> _endsceneOps;
};

class RenderFlowGraphParser
{
public:
	RenderFlowGraphParser();
	~RenderFlowGraphParser();

	ParsedRenderFlowGraphData parseRenderFlowGraph(std::string filepath);
};

