#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Lights/include/Light.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../GraphicsRendering/RenderDataStream/include/RenderDataStream.h"

#include "../../../../Solidum/GraphicsRendering/Mesh/include/mesh.h"

class LightComponent : public Component
{
private:
	Light* _light;
	mesh* _mesh;

	RenderDataStream* _graphicsStream = nullptr;

	bool _parentTransformDirty = false;
public:
	LightComponent(Light* light, mesh* mesh, std::string renderProcessName);
	~LightComponent();

	void update();
	void onEvent(EVENT_PTR evt);

};

