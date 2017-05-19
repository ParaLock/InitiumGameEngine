#pragma once
#include "Renderer.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"
#include "../../Shaders/include/IShader.h"
#include "../../Mesh/include/mesh.h"
#include "../../Material/include/Material.h"
#include "../../GPUPipeline/include/GPUPipeline.h"
#include "../../Lights/include/ILight.h"
#include "../../RenderParameters/include/RenderParams.h"
#include "../../GraphicsCommandList/include/GraphicsCommandList.h"
#include "../../RenderNodeTree/include/IRenderNodeTree.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../RenderNode/include/RenderNode.h"

class SkyRenderer : public Renderer
{
private:
	IShader* _skyShader;

	Matrix4f _wvp;
	Vector4f _skydomeApexColor;
	Vector4f _skydomeCenterColor;

	std::list<RenderNode*> _skyList;
public:
	SkyRenderer();
	~SkyRenderer();

	void DeferredInit();

	void gatherAndPrepareNodes(IRenderNodeTree* tree);
	void processNodes(GraphicsCommandList* commandList);
};

