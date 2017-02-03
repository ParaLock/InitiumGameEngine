#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Lights/include/ILight.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

class LightComponent : public Component
{
private:
	RenderOP _op;

	bool _parentTransformDirty = false;
public:
	LightComponent(ILight* light);
	~LightComponent();

	void update();
	void onEvent(EVENT_PTR evt);

};

