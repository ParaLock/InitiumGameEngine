#pragma once
#include "../../../sysInclude.h"

#include "../../RenderPass/include/RenderPassDescriptorParser.h"

class ShaderParser
{
private:
public:
	ShaderParser();
	~ShaderParser();

	std::list<std::string> getIncludeFile(std::string includeFilename);

	std::string parseShader(RenderPassDescriptorData* metadata, std::string filepath);
};

