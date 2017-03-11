#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../EngineUtils/include/quaternion.h"

enum ROT_DIR {
	ROT_LEFT,
	ROT_RIGHT,
	ROT_UP,
	ROT_DOWN
};

class Transform : public IResource
{
private:
	Vector3f _pos;

	Quaternion<float> _quaternion;

	Matrix4f _transformMatrix;
public:
	Transform();
	~Transform();

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void setRotation(float angleOfRot, ROT_DIR direction);
	void setPos(Vector3f pos);
	
	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	Matrix4f getMatrix() { return _transformMatrix; };

	Vector3f getPos() { return _pos; }
};

