#include "../include/RenderPassDescriptorParser.h"



RenderPassDescriptorParser::RenderPassDescriptorParser()
{
}


RenderPassDescriptorParser::~RenderPassDescriptorParser()
{
}

RenderPassDescriptorData RenderPassDescriptorParser::parseRenderPassDescriptor(std::string filepath)
{
	std::ifstream file(filepath);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("RenderPass descriptor file open failed!\n");
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

	RenderPassDescriptorData data;

	for each(std::string *str in *line) {
		std::vector<std::string> splitStr = StringManipulation::split(str, " ");

		if (splitStr.size() == 0)
			continue;

		if (splitStr.at(0) == "INPUT_HOOK") {

			RenderFlowGraphNodeIOHook hook;

			hook._userData = new RenderPassSpecificIOHookData();

			hook._type = splitStr.at(1);
			hook._index = std::stoi(splitStr.at(2));
			hook._isOutput = false;
			hook._name = splitStr.at(3);

			RenderPassSpecificIOHookData* specificData = (RenderPassSpecificIOHookData*)hook._userData;

			EnumString<SHADER_RESOURCE_TYPE>::To(specificData->_shaderResType, splitStr.at(1));

			data._hooksByName.insert({ hook._name, hook });
		}

		if (splitStr.at(0) == "OUTPUT_HOOK") {

			RenderFlowGraphNodeIOHook hook;

			hook._userData = new RenderPassSpecificIOHookData();

			hook._type = splitStr.at(1);
			hook._index = std::stoi(splitStr.at(2));
			hook._isOutput = true;
			hook._name = splitStr.at(3);

			RenderPassSpecificIOHookData* specificData = (RenderPassSpecificIOHookData*)hook._userData;

			EnumString<SHADER_RESOURCE_TYPE>::To(specificData->_shaderResType, splitStr.at(1));

			data._hooksByName.insert({ hook._name, hook });
		}

		if (splitStr.at(0) == "NAME") {
			data._renderPassName = splitStr.at(1);
		}

		if (splitStr.at(0) == "SHADER") {
			data._shadersToLoad.push_back(ShaderToLoad(splitStr.at(1), splitStr.at(2)));
		}
	}

	return data;
}
