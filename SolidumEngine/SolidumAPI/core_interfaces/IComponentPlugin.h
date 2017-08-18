#pragma once

#include "IPlugin.h"

class IComponentPlugin : public IPlugin {
private:
public:

	PLUGIN_TYPE getType() { return PLUGIN_TYPE::COMPONENT_PLUGIN; }

	virtual void update(float delta) = 0;

};