#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../ResourceFramework/include/ResourceInitParams.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "../../../EngineUtils/include/quaternion.h"

enum ROT_DIR {
	ROT_LEFT,
	ROT_RIGHT,
	ROT_UP,
	ROT_DOWN
};

class ResourcePool;

class Transform : public Resource<Transform, GenericFactory, ResourcePool>
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

	struct InitData : public ResourceInitParams {

		

		InitData() {}
	};

	void buildTransform();

	void load() { };
	void unload() { };

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

