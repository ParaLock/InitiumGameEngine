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

#include "../../Particles/include/ParticleRenderNode.h"

#include "../../GraphicsCore/include/IGraphicsCore.h"

#include "../../RenderNode/include/RenderNode.h"

class ParticleRenderer : public Renderer
{
private:
	IShader* _particleRenderingShader;

	std::list<RenderNode*> _particleRenderNodes;

public:
	ParticleRenderer();
	~ParticleRenderer();

	Matrix4f createParticleMVMatrix(Vector3f pos, float rotation, float scale,
		const Matrix4f& matView, const Matrix4f matWorld);

	void DeferredInit();

	void gatherAndPrepareNodes(IRenderNodeTree* tree);
	void processNodes(GraphicsCommandList* commandList);
};

