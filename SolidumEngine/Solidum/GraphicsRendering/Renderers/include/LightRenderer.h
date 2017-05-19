#pragma once
#include "Renderer.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"
#include "../../Shaders/include/IShader.h"
#include "../../Mesh/include/mesh.h"
#include "../../Material/include/Material.h"
#include "../../GPUPipeline/include/GPUPipeline.h"
#include "../../Lights/include/ILight.h"
#include "../../Lights/include/Light.h"
#include "../../RenderParameters/include/RenderParams.h"
#include "../../GraphicsCommandList/include/GraphicsCommandList.h"
#include "../../RenderNodeTree/include/IRenderNodeTree.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../RenderNode/include/RenderNode.h"

class LightRenderer : public Renderer
{
private:
	IShader* _pointLightShader;
	IShader* _directionalLightShader;

	mesh* _screenQuad;

	std::list<RenderNode*> _lights;
public:
	LightRenderer();
	~LightRenderer();

	void DeferredInit();

	void gatherAndPrepareNodes(IRenderNodeTree* tree);

	void processNodes(GraphicsCommandList* commandList);
};

