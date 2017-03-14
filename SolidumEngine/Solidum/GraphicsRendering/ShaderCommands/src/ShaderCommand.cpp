#include "../include/ShaderCommand.h"



ShaderCommand::ShaderCommand()
{
}


ShaderCommand::~ShaderCommand()
{
}

void ShaderUpdateUniformCommand::execute()
{
	_shader->updateUniform(_uniform.first, _uniform.second);
}

void ShaderUpdateLightUniformsCommand::execute()
{
	if(_shader->getRenderMode() == SHADER_RENDER_TYPE::DEFERRED_RENDERING_LIGHT) {
		if (_lights.size() > 0)
			_shader->updateDeferredLightUniforms(_lights.at(0));
	}
	if(_shader->getRenderMode() == SHADER_RENDER_TYPE::FORWARD_RENDERING) {
		if (_lights.size() > 0)
		{
			if (_lights.at(0)->getType() == LIGHT_TYPE::POINT_LIGHT) {
				_shader->updatePointLightsForwardRendering(_lights);
			}
			if (_lights.at(0)->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {
				_shader->updateDirectionalLightsForwardRendering(_lights);
			}
		}
	}
}

void ShaderUpdateMaterialPassUniformsCommand::execute()
{
	_shader->updateMaterialPassUniforms(_matPass);
}

void ShaderUpdateCameraUniformsCommand::execute()
{
	_shader->updateCameraUniforms(_camera);
}

void ShaderUpdateTransformCommand::execute()
{
	_shader->updateModelUniforms(_transform);
}

void ShaderUpdateModelMeshCommand::execute()
{
	_shader->setMesh(_mesh);
}

void ShaderUpdateModelTexCommand::execute()
{
	_shader->setModelTexture(_tex);
}

void ShaderSyncUniforms::execute()
{
	_shader->updateGPU();
}
