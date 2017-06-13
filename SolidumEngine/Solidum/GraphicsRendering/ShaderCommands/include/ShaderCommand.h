#pragma once
#include "../../../sysInclude.h"

#include "../../Shaders/include/IShader.h"
#include "../../Lights/include/ILight.h"
#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../Shaders/include/ShaderUniformGroup.h"

class MaterialPass;
class CameraComponent;
class Transform;
class mesh;
class Texture;

class ShaderCommand : public GraphicsCommand
{
public:
	ShaderCommand();
	~ShaderCommand();
};

class ShaderUpdateUniformCommand : public ShaderCommand {
private:
	std::shared_ptr<ShaderUniformGroup> _uniforms;
	IShader* _shader;
public:
	ShaderUpdateUniformCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM; }

	struct InitData : public IResourceBuilder {

		std::shared_ptr<ShaderUniformGroup> _uniforms;
		IShader* _shader;
		
		InitData(std::shared_ptr<ShaderUniformGroup> uniform, IShader* shader) {
			_uniforms = uniform;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_uniforms = realBuilder->_uniforms;
		_shader = realBuilder->_shader;
	}

	void execute();
};

class ShaderSyncUniforms : public ShaderCommand {
private:
	IShader* _shader;
public:
	ShaderSyncUniforms() { _type = GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS; }

	struct InitData : public IResourceBuilder {
		IShader* _shader;

		InitData(IShader* shader) {
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_shader = realBuilder->_shader;
	}

	void execute();
};