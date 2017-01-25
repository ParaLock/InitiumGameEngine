#pragma once

#include "IEvent.h"

#include "../../GraphicsRendering/Transform/include/Transform.h"

class RenderEvent : public IEvent
{
private:

	std::string _meshID = "null";
	std::string _texID = "null";
	std::string _matID = "null";
	std::string _shaderID = "null";
	std::string _lightID = "null";

	Transform* _transform;

public:
	RenderEvent();
	~RenderEvent();

	std::string getMeshID() { return _meshID; };
	std::string getTexID() { return _texID; };
	std::string getMatID() { return _matID; };
	std::string getShaderID() { return _shaderID; };
	std::string getLightID() { return _lightID; }

	Transform* getTransform() { return _transform; }

	void setMeshID(std::string meshID) { _meshID = meshID; };
	void setTextureID(std::string texID) { _texID = texID; };
	void setMaterialID(std::string matID) { _matID = matID; };
	void setShaderID(std::string shaderID) { _shaderID = shaderID; };
	void setLightID(std::string lightID) { _lightID = lightID; }

	void setTransform(Transform* transform) { _transform = transform; }
};

