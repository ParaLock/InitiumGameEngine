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
	Vector3f _vecPos;
	Vector3f _vecScale;

	Quaternion<float> _quaternion;

	Matrix4f _localTransformMatrix;
	Matrix4f _globalTransformMatrix;

	Transform* _parent = nullptr;
public:
	Transform();
	~Transform();

	void buildTransform();

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void setParent(Transform* transform);
	void setGlobalTransform(Matrix4f global);

	void setPosition(Vector3f pos);
	void setScale(Vector3f scale);
	void setRotation(Vector3f axis, float angle);

	void setGlobalOrigin(Vector3f vecOrigin);

	Transform* getParent() { return _parent; }

	Vector3f getGlobalOrigin();

	Matrix4f getGlobalTransform();

	Vector3f getPos() { return Matrix4f::getPos(_globalTransformMatrix); }
};

