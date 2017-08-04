#include "../include/RenderFlowGraphParser.h"



RenderFlowGraphParser::RenderFlowGraphParser()
{
}


RenderFlowGraphParser::~RenderFlowGraphParser()
{
}

ParsedRenderFlowGraphData RenderFlowGraphParser::parseRenderFlowGraph(std::string filepath, ResourceCreator* resCreator)
{
	std::ifstream file(filepath);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("Renderer descriptor file open failed!\n");
	}
	else {
		char buf[256];

		while (!file.eof())
		{
			file.getline(buf, 256);

			if (buf[0] != 0)
				line->push_back(new std::string(buf));
		}
	}

	ParsedRenderFlowGraphData data;
	ParsedNodeData currentNodeData;

	bool inEdge = false;

	for each(std::string *str in *line) {

		std::string parsedLine = std::string();;

		std::vector<std::string> spaceSplit = StringManipulation::split(str, " ");

		std::vector<std::string> hookSplit = StringManipulation::split(str, "!%");

		if (spaceSplit.size() == 0)
			continue;

		if (spaceSplit.at(0) == "INIT") {

			if (spaceSplit.at(1) == "RENDER_TARGET") {
				int height = 1;
				int width = 1;

				TEX_FORMAT rtTexFormat = TEX_FORMAT::RGBA_32BIT_FLOAT;

				if (spaceSplit.size() >= 4) {

					height = std::stoi(spaceSplit.at(4));
					width = std::stoi(spaceSplit.at(3));

				}
				else {
					height = window::getInstance()->screen_height;
					width = window::getInstance()->screen_width;

				}

				resCreator->createResourceImmediate<RenderTarget>(&RenderTarget::InitData(rtTexFormat, height, width), spaceSplit.at(2),
					[=](IResource* res) {IResource::addResourceToGroup(res, std::string("RenderTargetGroup"), resCreator->getParentEngine()); });

			}

			if (spaceSplit.at(1) == "TEXTURE_SAMPLER") {

				TEX_ADDR_MODES addrMode;
				TEX_FILTERS filterType;

				if (spaceSplit.at(2) == "WRAP") {
					addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_WRAP;
				}
				if (spaceSplit.at(2) == "CLAMP") {
					addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_CLAMP;
				}

				if (spaceSplit.at(3) == "LINEAR") {
					filterType = TEX_FILTERS::TEX_FILTER_LINEAR;
				}

				if (spaceSplit.at(3) == "POINT") {
					filterType = TEX_FILTERS::TEX_FILTER_POINT;
				}

				resCreator->createResourceImmediate<TextureSampler>(&TextureSampler::InitData(filterType, ANISOTRPHIC_FILTER_LEVELS::NO_ANISOTROPHIC_FILTERING, addrMode), 
					spaceSplit.at(4), [=](IResource* res) {IResource::addResourceToGroup(res, std::string("TextureSamplerGroup"), resCreator->getParentEngine()); });
			}

			if (spaceSplit.at(1) == "DEPTH_STENCIL") {

				if (spaceSplit.size() >= 4) {


					resCreator->createResourceImmediate<DepthStencil>(&DepthStencil::InitData(std::stoi(spaceSplit.at(3)), std::stoi(spaceSplit.at(4))), spaceSplit.at(2),
						[=](IResource* res) {IResource::addResourceToGroup(res, std::string("DepthStencilGroup"), resCreator->getParentEngine()); });

				}
				else {

					resCreator->createResourceImmediate<DepthStencil>(&DepthStencil::InitData(window::getInstance()->screen_width, window::getInstance()->screen_height), spaceSplit.at(2),
						[=](IResource* res) {IResource::addResourceToGroup(res, std::string("DepthStencilGroup"), resCreator->getParentEngine()); });
				}

			}
		}

		if (spaceSplit.at(0) == "OP") {
			ParsedRenderFlowGraphOP renderOP;
			
			renderOP._opType = spaceSplit.at(1);
			renderOP._targetType = spaceSplit.at(2);
			renderOP._targetName = spaceSplit.at(3);

			data._endsceneOps.push_back(renderOP);
		}

		if (spaceSplit.at(0) == "RESOURCE_INITIALIZATION_BEGIN") {

		}

		if (spaceSplit.at(0) == "NODE") {

			currentNodeData = ParsedNodeData();
		}

		if (spaceSplit.at(0) == "NODE_END") {
			data._nodes.push_back(currentNodeData);
		}

		if (spaceSplit.at(0) == "EDGES_BEGIN") {

			inEdge = true;
		}
		if (spaceSplit.at(0) == "EDGES_END") {
			inEdge = false;
		}

		if (spaceSplit.at(0) == "CORE_NAME") {
			data._orderedNodeNames.push_back(spaceSplit.at(1));
			currentNodeData._coreName = spaceSplit.at(1);
		}

		if (spaceSplit.at(0) == "OUTPUT" && inEdge) {
			ParsedNodeEdge edge;

			edge._type = spaceSplit.at(1);
			edge._index = std::stoi(spaceSplit.at(2));
			edge._name = spaceSplit.at(3);
			edge._isOutput = true;

			currentNodeData._edges.push_back(edge);
		}

		if (spaceSplit.at(0) == "INPUT" && inEdge) {
			ParsedNodeEdge edge;

			edge._type = spaceSplit.at(1);
			edge._index = std::stoi(spaceSplit.at(2));
			edge._name = spaceSplit.at(3);
			edge._isOutput = false;

			currentNodeData._edges.push_back(edge);
		}
	}

	return data;
}
