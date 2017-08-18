#pragma once

enum class PLUGIN_TYPE {
	COMPONENT_PLUGIN,
	RENDER_PASS_PLUGIN
};

class IPlugin {
private:
public:
	virtual PLUGIN_TYPE getType() = 0;
};