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
public:
	LightRenderNode(uint64_t id);
	~LightRenderNode();

	ILight* getLight() { return _renderParams.getPerNodeParam_Light(); }

	bool isRenderViable();

	virtual void* getVar(std::string varname);

	void render();
};

