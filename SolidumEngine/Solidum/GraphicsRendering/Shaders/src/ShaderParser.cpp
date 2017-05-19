#include "../include/ShaderParser.h"



ShaderParser::ShaderParser()
{
}


ShaderParser::~ShaderParser()
{
}

std::list<std::string> ShaderParser::getIncludeFile(std::string includeFilename)
{
	std::string includeFilePath = "./res/Shaders/deferredRendering/basicShaders/" + includeFilename;

	includeFilePath.erase(std::remove(includeFilePath.begin(), includeFilePath.end(), '"'), includeFilePath.end());

	std::ifstream includeFile(includeFilePath);

	std::vector<std::string*> *includeLines = new std::vector<std::string*>;

	if (!includeFile.is_open())
	{
		printf("Shader Include file open failed!\n");
	}
	else {
		char buf[256];

		while (!includeFile.eof())
		{
			includeFile.getline(buf, 256);

			if (buf[0] != 0)
				includeLines->push_back(new std::string(buf));
		}
	}

	std::list<std::string> includeFileLines;

	for each(std::string *str in *includeLines) {

		std::vector<std::string> spaceSplit = StringManipulation::split(str, " ");

		if (spaceSplit.size() != 0) {
			if (spaceSplit.at(0) == "#include") {

				std::list<std::string> recursiveIncludeLines = getIncludeFile(spaceSplit.at(1));

				for each(std::string recIncLine in recursiveIncludeLines) {
					includeFileLines.push_back(recIncLine);
				}

				continue;
			}
		}

		includeFileLines.push_back(*str);
	}

	return includeFileLines;
}

std::string ShaderParser::parseShader(RendererDescriptorData * metadata, std::string filepath)
{
	std::string parsedShader;

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

	std::string languageType = "HLSL";

	std::list<std::string> linesWIncludes;

	for each(std::string *str in *line) {
		std::string parsedLine = *str;

		parsedLine.erase(std::remove(parsedLine.begin(), parsedLine.end(), '\t'), parsedLine.end());

		std::vector<std::string> spaceSplit = StringManipulation::split(str, " ");

		if (spaceSplit.size() == 0)
			continue;

		if (spaceSplit.at(0) == "#include") {

			linesWIncludes = getIncludeFile(spaceSplit.at(1));

			continue;
		}
	}

	std::list<std::string> finalShader;

	for each(std::string includeLine in linesWIncludes) {

		finalShader.push_back(includeLine);
	}

	for each(std::string *str in *line) {

		std::vector<std::string> spaceSplit = StringManipulation::split(str, " ");

		if (spaceSplit.size() == 0)
			continue;

		if (spaceSplit.at(0) == "#include")
			continue;
		
		finalShader.push_back(*str);
	}


	for each(std::string str in finalShader) {

		std::string parsedLine = str;

		parsedLine.erase(std::remove(parsedLine.begin(), parsedLine.end(), '\t'), parsedLine.end());

		std::vector<std::string> spaceSplit = StringManipulation::split(&str, " ");

		std::vector<std::string> hookSplit = StringManipulation::split(&str, "!%");

		if (spaceSplit.size() == 0) 
			continue;

		if (hookSplit.size() >= 2) {

			std::vector<std::string> hookSpaceSplit = StringManipulation::split(&hookSplit[1], " ");

			auto itr = metadata->_hooksByName.find(hookSpaceSplit.at(1));

			if (itr != metadata->_hooksByName.end()) {

				RenderFlowGraphNodeIOHook* hookData = &metadata->_hooksByName.at(hookSpaceSplit.at(1));
				RendererSpecificIOHookData* specificData = (RendererSpecificIOHookData*)hookData->_userData;

				if (languageType == "HLSL") {

					if (hookSpaceSplit.at(0) == "PIXEL_SHADER") {
						specificData->_shaderType = SHADER_TYPE::PIXEL_SHADER;
					}

					if (hookSpaceSplit.at(0) == "VERTEX_SHADER") {
						specificData->_shaderType = SHADER_TYPE::VERTEX_SHADER;
					}

					if (hookData->_isOutput) {
						parsedLine = str.substr(0, str.find(":") + 1);

						parsedLine.append(" SV_Target" + std::to_string(hookData->_index) + "; ");
					}
					else {
						parsedLine = str.substr(0, str.find(":") + 1);

						std::string _typeToken;

						if (specificData->_shaderResType == SHADER_RESOURCE_TYPE::RENDER_TARGET || specificData->_shaderResType == SHADER_RESOURCE_TYPE::TEXTURE) {
							_typeToken = "t";
						}

						if (specificData->_shaderResType == SHADER_RESOURCE_TYPE::TEXTURE_SAMPLER) {
							_typeToken = "s";
						}

						parsedLine.append(" register(" + _typeToken + std::to_string(hookData->_index) + "); ");
					}
				}
			}
		}

		parsedShader.append(parsedLine);
	}

	return parsedShader;
}
