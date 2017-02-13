#include "../include/RenderProcess.h"



RenderProcess::RenderProcess()
{
	_registeredStreams = new std::list<RenderDataStream*>;

	_passes = new std::list<RenderPass>;
}


RenderProcess::~RenderProcess()
{
	delete _registeredStreams;
	delete _passes;
}

void RenderProcess::load(IResourceBuilder * builder)
{
	RenderProcessBuilder* realBuilder = static_cast<RenderProcessBuilder*>(builder);

	_resManagerPool = realBuilder->_resManagerPool;

	std::wstring filePathWStr(realBuilder->_filename);

	std::string filepathSTLStr = StringManipulation::ws2s(filePathWStr);

	std::ifstream file(realBuilder->_filename);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("Pipeline descriptor file open failed!\n");
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

	RenderPass currentPass;

	for (size_t i = 0; i < line->size(); i++) 
	{
		std::vector<std::string> tokens = StringManipulation::split(line->at(i), ' ');
	
		if (tokens.at(0) == "RENDER_PROCESS") {
			if (tokens.size() < 3) {

				isDeferred = false;
			}
			else {

				if (tokens.at(1) == "[DEFERRED]") {

					isDeferred = true;

					currentPass.setName(tokens.at(2));
				}
			}
		}

		if (tokens.at(0) == "PASS") {

			currentPass.setName(tokens.at(1));
		}

		if (tokens.at(0) == "END_PASS") {
			_passes->push_back(currentPass);
		}

		if (tokens.at(0) == "SHADER") {
			Shader* shader = realBuilder->_resManagerPool->getResourceManager("ShaderManager")->
				getResource(tokens.at(1))->getCore<Shader>();
				
			if (shader != nullptr)
			{
				currentPass.setShader(shader);
			}		
		}

		if (tokens.at(0) == "PIPELINE") {
			GPUPipeline* pipelineState = realBuilder->_resManagerPool->getResourceManager("GPUPipelineManager")->
				getResource(tokens.at(1))->getCore<GPUPipeline>();

			if (pipelineState != nullptr)
			{
				currentPass.setPipeline(pipelineState);
			}
		}
	}

	isLoaded = true;
}

void RenderProcess::unload()
{
	isLoaded = false;
}

void RenderProcess::registerDataStream(RenderDataStream * stream)
{
	_registeredStreams->push_back(stream);
}

void RenderProcess::execute()
{
	for (auto streamItr = _registeredStreams->begin(); streamItr != _registeredStreams->end(); streamItr++) {

		for (auto passItr = _passes->begin(); passItr != _passes->end(); passItr++) {

			passItr->execute(*streamItr);
		}

		RenderDataStream* stream = *streamItr;

		stream->flushStream();
	}
}
