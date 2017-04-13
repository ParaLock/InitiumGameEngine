#pragma once
#include "Component.h"

#include "../../../GraphicsRendering/RenderNode/include/LightRenderNode.h"

#include "../../../GraphicsRendering/Lights/include/Light.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

class LightComponent : public Component
{
private:
	Light* _light;

	bool _parentTransformDirty = false;

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
public:
	LightComponent(Light* light, int index);
	~LightComponent();

	void init();

	void update(float delta);

	void onEvent(EVENT_PTR evt);

};

