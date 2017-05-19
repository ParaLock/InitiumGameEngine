#pragma once
#include "../../../sysInclude.h"

#include "../../Renderers/include/RendererDescriptorParser.h"

class ShaderParser
{
private:
public:
	ShaderParser();
	~ShaderParser();

	std::list<std::string> getIncludeFile(std::string includeFilename);

	std::string parseShader(RendererDescriptorData* metadata, std::string filepath);
};

