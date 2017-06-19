#pragma once
#include "Component.h"

#include "../../../GraphicsRendering/Lights/include/Light.h"

#include "../../../GraphicsRendering/Mesh/include/mesh.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataGroup.h"

#include "../../../WorldSimulation/include/World.h"

struct RenderPassPacket_LightData {

	int _indiceCount;
	IResource* _indexBuff;
	IResource* _vertexBuff;

	Matrix4f _shadowView;
	Matrix4f _projectionMatrix;
	Matrix4f _viewMatrix;

	LIGHT_TYPE _lightType;

	Vector3f _lightPos;
	Vector3f _lightDirection;
	Vector4f _lightColor;

	float _pointLightRange;

	float _pointLightExponent;
	float _pointLightConstant;
	float _pointLightLinear;

	float _intensity;

	bool _castsShadows;
};

class LightComponent : public Component
{
private:
	Light* _light;

	mesh* _screenQuad;

	bool _parentTransformDirty = false;

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
public:
	LightComponent(Light* light, int index, IEntity* entity);
	~LightComponent();

	void update(float delta);

	void onEvent(EVENT_PTR evt);

	void AddRenderData(RenderDataGroup* collection);
};

