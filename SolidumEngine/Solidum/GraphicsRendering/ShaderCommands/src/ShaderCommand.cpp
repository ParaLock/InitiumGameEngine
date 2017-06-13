#include "../include/ShaderCommand.h"



ShaderCommand::ShaderCommand()
{
}


ShaderCommand::~ShaderCommand()
{
}

void ShaderUpdateUniformCommand::execute()
{
	auto& itr = _uniforms->getUniformsMap().begin();
	auto& itr_end = _uniforms->getUniformsMap().end();

	while (itr != itr_end) {

		auto& uniform = *itr;

		_shader->updateUniform(uniform.first, uniform.second.get());

		itr++;
	}
}

void ShaderSyncUniforms::execute()
{
	_shader->updateGPU();
}
