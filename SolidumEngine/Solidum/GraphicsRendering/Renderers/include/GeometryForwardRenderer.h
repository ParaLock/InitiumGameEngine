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
#include "../../RenderNodeTree/include/RenderNodeTree.h"

#include "../../RenderNode/include/LightRenderNode.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"



#include "../../RenderNode/include/RenderNode.h"

class GeometryForwardRenderer : public Renderer
{
private:
	std::list<RenderNode*> _staticMeshes;
public:
	GeometryForwardRenderer();
	~GeometryForwardRenderer();

	void gatherAndPrepareNodes(IRenderNodeTree* tree);
	void processNodes(GraphicsCommandList* commandList);
};
