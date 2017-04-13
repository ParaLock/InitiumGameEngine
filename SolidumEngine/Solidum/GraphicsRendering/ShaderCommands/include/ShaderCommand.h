#pragma once
#include "../../../sysInclude.h"

#include "../../Shaders/include/IShader.h"
#include "../../Lights/include/ILight.h"
#include "../../GraphicsCommand/include/GraphicsCommand.h"

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
	std::pair<std::string, void*> _uniform;
	IShader* _shader;
public:
	ShaderUpdateUniformCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM; }

	struct InitData : public IResourceBuilder {
		std::pair<std::string, void*> _uniform;
		IShader* _shader;
		
		InitData(std::pair<std::string, void*> uniform, IShader* shader) {
			_uniform = uniform;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_uniform = realBuilder->_uniform;
		_shader = realBuilder->_shader;
	}

	void execute();
};

class ShaderUpdateLightUniformsCommand : public ShaderCommand {
private:
	std::vector<ILight*> _lights;
	IShader* _shader;
public:
	ShaderUpdateLightUniformsCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS; }

	struct InitData : public IResourceBuilder {
		std::vector<ILight*> _lights;
		IShader* _shader;

		InitData(std::list<ILight*> lights, IShader* shader) {
			for each(ILight* light in lights) _lights.push_back(light);
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_lights = realBuilder->_lights;
		_shader = realBuilder->_shader;
	}

	void execute();
};

class ShaderUpdateMaterialPassUniformsCommand : public ShaderCommand {
private:
	MaterialPass* _matPass;
	IShader* _shader;
public:
	ShaderUpdateMaterialPassUniformsCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_MATERIAL_PASS_UNIFORMS; }

	struct InitData : public IResourceBuilder {
		MaterialPass* _matPass;
		IShader* _shader;

		InitData(MaterialPass* matPass, IShader* shader) {
			_matPass = matPass;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {

		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_matPass = realBuilder->_matPass;
		_shader = realBuilder->_shader;
	}

	void execute();
};

class ShaderUpdateCameraUniformsCommand : public ShaderCommand {
private:
	CameraComponent* _camera;
	IShader* _shader;
public:
	ShaderUpdateCameraUniformsCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS; };

	struct InitData : public IResourceBuilder {
		CameraComponent* _camera;
		IShader* _shader;

		InitData(CameraComponent* camera, IShader* shader) {
			_camera = camera;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_shader = realBuilder->_shader;
		_camera = realBuilder->_camera;
	}

	void execute();
};

class ShaderUpdateTransformCommand : public ShaderCommand {
private:
	Transform* _transform;
	IShader* _shader;
public:
	ShaderUpdateTransformCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS; }

	struct InitData : public IResourceBuilder {
		Transform* _transform;
		IShader* _shader;

		InitData(Transform* transform, IShader* shader) {
			_transform = transform;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_transform = realBuilder->_transform;
		_shader = realBuilder->_shader;
	}

	void execute();
};

class ShaderUpdateModelMeshCommand : public ShaderCommand {
private:
	mesh* _mesh;
	IShader* _shader;
public:

	ShaderUpdateModelMeshCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_MESH; }

	struct InitData : public IResourceBuilder {

		mesh* _mesh;
		IShader* _shader;

		InitData(mesh* mesh, IShader* shader) {
			_mesh = mesh;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_mesh = realBuilder->_mesh;
		_shader = realBuilder->_shader;
	}

	void execute();

};

class ShaderUpdateModelTexCommand : public ShaderCommand {
private:
	Texture* _tex;
	IShader* _shader;
public:
	ShaderUpdateModelTexCommand() { _type = GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_MODEL_TEX; }

	struct InitData : public IResourceBuilder {

		Texture* _tex;
		IShader* _shader;

		InitData(Texture* tex, IShader* shader) {
			_tex = tex;
			_shader = shader;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) {
		InitData* realBuilder = static_cast<InitData*>(builder.get());

		_tex = realBuilder->_tex;
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