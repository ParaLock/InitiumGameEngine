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
	ShaderUpdateUniformCommand(void* data, std::string uniformName, IShader* shader) {
		_uniform = std::make_pair(uniformName, data);
		_shader = shader;
	}

	void execute();
};

class ShaderUpdateLightUniformsCommand : public ShaderCommand {
private:
	std::vector<ILight*> _lights;
	IShader* _shader;
public:

	ShaderUpdateLightUniformsCommand(std::vector<ILight*> lights, IShader* shader) {
		_lights = lights;
		_shader = shader;
	}

	void execute();
};

class ShaderUpdateMaterialPassUniformsCommand : public ShaderCommand {
private:
	MaterialPass* _matPass;
	IShader* _shader;
public:
	ShaderUpdateMaterialPassUniformsCommand(MaterialPass* pass, IShader* shader) {
		_matPass = pass;
		_shader = shader;
	}

	void execute();
};

class ShaderUpdateCameraUniformsCommand : public ShaderCommand {
private:
	CameraComponent* _camera;
	IShader* _shader;
public:
	ShaderUpdateCameraUniformsCommand(CameraComponent* camera, IShader* shader) {
		_camera = camera;
		_shader = shader;
	}

	void execute();
};

class ShaderUpdateTransformCommand : public ShaderCommand {
private:
	Transform* _transform;
	IShader* _shader;
public:
	ShaderUpdateTransformCommand(Transform* transform, IShader* shader) {
		_transform = transform;
		_shader = shader;
	}

	void execute();
};

class ShaderUpdateModelMeshCommand : public ShaderCommand {
private:
	mesh* _mesh;
	IShader* _shader;
public:

	ShaderUpdateModelMeshCommand(mesh* mesh, IShader* shader) {
		_mesh = mesh;
		_shader = shader;
	}

	void execute();

};

class ShaderUpdateModelTexCommand : public ShaderCommand {
private:
	Texture* _tex;
	IShader* _shader;
public:

	ShaderUpdateModelTexCommand(Texture* tex, IShader* shader) {
		_tex = tex;
		_shader = shader;
	}

	void execute();
};

class ShaderSyncUniforms : public ShaderCommand {
private:
	IShader* _shader;
public:
	ShaderSyncUniforms(IShader* shader) {
		_shader = shader;
	}

	void execute();
};