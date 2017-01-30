#pragma once
#include "../../../sysInclude.h"

class mesh;
class Shader;
class GPUPipeline;
class Texture;
class Material;
class ILight;
class Transform;

class camera;

class RenderOP
{
private:
	mesh* _mesh = nullptr;
	Shader* _shader = nullptr;
	Texture* _tex = nullptr;
	Material* _mat = nullptr;

	ILight* _light = nullptr;

	Transform* _transform = nullptr;

	camera* _cam = nullptr;
public:
	RenderOP();
	~RenderOP();

	void setMesh(mesh* mesh) { _mesh = mesh; }
	void setLight(ILight* light) { _light = light; }
	void setShader(Shader* shader) { _shader = shader; }
	void setTexture(Texture* tex) { _tex = tex; }
	void setMaterial(Material* mat) { _mat = mat; }
	void setTransform(Transform* transform) { _transform = transform; }
	void setCamera(camera* cam) { _cam = cam; }

	mesh* getMesh() { return _mesh; }
	ILight* getLight() { return _light; }
	Shader* getShader() { return _shader; }
	Texture* getTexture() { return _tex; }
	Material* getMaterial() { return _mat; }
	Transform* getTransform() { return _transform; }
	camera* getCamera() { return _cam; }
};

