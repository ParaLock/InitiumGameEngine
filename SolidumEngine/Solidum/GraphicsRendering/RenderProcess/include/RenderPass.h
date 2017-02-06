#pragma once
#include "../../../sysInclude.h"

#include "../../RenderDataStream/include/RenderDataStream.h"

#include "../../Shaders/include/Shader.h"
#include "../../GPUPipeline/include/GPUPipeline.h"
#include "../../Material/include/Material.h"
#include "../../Lights/include/Light.h"

class RenderPass
{
private:
	Shader* _shader = nullptr;
	GPUPipeline* _pipelineStateObject = nullptr;

	std::string _name;
public:
	RenderPass();
	~RenderPass();

	void setShader(Shader* shader) { _shader = shader; }
	void setPipeline(GPUPipeline* pipe) { _pipelineStateObject = pipe; }
	void setName(std::string name) { _name = name; };

	Shader* getShader() { return _shader; }

	void execute(RenderDataStream* stream);
};

