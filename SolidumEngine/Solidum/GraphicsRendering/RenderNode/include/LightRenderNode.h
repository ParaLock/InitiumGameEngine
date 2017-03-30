#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"

#include "../../Shaders/include/Shader.h"

#include "../../Lights/include/Light.h"

#include "../../Lights/include/LightManager.h"

class LightRenderNode : public RenderNode
{
private:
	mesh* _orthoMesh;
	Light* _light;
public:
	LightRenderNode(Light* light, uint64_t id);
	~LightRenderNode();

	ILight* getLight() { return _light; }

	virtual void* getVar(std::string varname);

	void render();
};

