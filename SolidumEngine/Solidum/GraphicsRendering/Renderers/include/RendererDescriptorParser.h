#pragma once
#include "../../RenderFlowGraph/include/RenderFlowGraphIOInterface.h"
#include "../../../EngineUtils/include/StringManipulation.h"
#include "../../../sysInclude.h"

class IResource;

struct ShaderToLoad {

	ShaderToLoad(std::string path, std::string name) {
		_path = path;
		_name = name;
	}

	std::string _path;
	std::string _name;
};

struct RendererDescriptorData {

	std::string _rendererName;

	std::list<ShaderToLoad> _shadersToLoad;

	std::map<std::string, RenderFlowGraphNodeIOHook> _hooksByName;
};

class RendererDescriptorParser
{
private:
public:
	RendererDescriptorParser();
	~RendererDescriptorParser();

	RendererDescriptorData parseRenderDescriptor(std::string filepath);
};

