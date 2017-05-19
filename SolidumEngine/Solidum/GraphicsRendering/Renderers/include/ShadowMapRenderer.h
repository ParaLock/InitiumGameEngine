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

#include "../../RenderNode/include/LightRenderNode.h"
#include "../../RenderNode/include/MeshRenderNode.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"
#include "../../RenderNode/include/RenderNode.h"


class ShadowMapRenderer : public Renderer
{
private:
	IShader* _shadowGenShader;

	std::list<RenderNode*> _lights;
	std::list<RenderNode*> _meshes;
public:
	ShadowMapRenderer();
	~ShadowMapRenderer();

	void DeferredInit();

	void gatherAndPrepareNodes(IRenderNodeTree* tree);
	void processNodes(GraphicsCommandList* commandList);
};

