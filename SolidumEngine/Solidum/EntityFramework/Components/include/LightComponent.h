#pragma once
#include "Component.h"

#include "../../../GraphicsRendering/RenderNode/include/LightRenderNode.h"

#include "../../../GraphicsRendering/Lights/include/Light.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

class LightComponent : public Component
{
private:
	Light* _light;

	std::list<uint64_t> _renderNodes;

	bool _parentTransformDirty = false;
public:
	LightComponent(Light* light);
	~LightComponent();

	void update();

	void onEvent(EVENT_PTR evt);

};

