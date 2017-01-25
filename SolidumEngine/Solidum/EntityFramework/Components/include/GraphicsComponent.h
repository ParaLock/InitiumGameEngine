#pragma once
#include "../../../sysInclude.h"

#include "../../../EventFramework/include/RenderEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "IComponent.h"

class GraphicsComponent : public IComponent
{
private:

	std::string _meshID = "null";
	std::string _texID = "null";
	std::string _matID = "null";
	std::string _shaderID = "null";

	std::string _lightID;

	Transform* _transform;
public:
	GraphicsComponent(std::string meshID, std::string texID, 
		std::string matID, std::string shaderID, std::string lightID, Transform* transform);
	~GraphicsComponent();
	
	void setMesh(std::string meshID) { _meshID = meshID; };
	void setTexture(std::string texID) { _texID = texID; };
	void setMaterial(std::string matID) { _matID = matID; };
	void setShader(std::string shaderID) { _shaderID = shaderID; };
	void setLight(std::string lightID) { _lightID = lightID; };

	std::string getMesh() { return _meshID; };
	std::string getTexture() { return _texID; };
	std::string getMaterial() { return _matID; };
	std::string getShader() { return _shaderID; };
	std::string getLight() { return _lightID; };

	Transform* getTransform() { return _transform; };

	void onEvent(IEvent* evt) {}

	void update();
};

