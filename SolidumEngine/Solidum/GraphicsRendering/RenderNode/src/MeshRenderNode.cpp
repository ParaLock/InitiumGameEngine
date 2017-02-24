#include "../include/MeshRenderNode.h"



MeshRenderNode::MeshRenderNode(mesh* mesh, Texture* texture, MaterialPass* pass) :
	_mesh(mesh),
	_texture(texture),
	_pass(pass)
{
	_shader = _pass->getShader();

	_type = RENDER_NODE_TYPE::MESH_RENDER_NODE;
}


MeshRenderNode::~MeshRenderNode()
{
}

void MeshRenderNode::render()
{
	if (_isVisible) {

		if (_renderParams.getPerNodeParam_ForwardRendering()) {

			std::vector<RenderNode*> lightNodes = GraphicsCore::getInstance()->getRenderNodeTree()->queryAllLights();

			std::vector<ILight*> lights;

			for each (RenderNode* node in lightNodes) {
				LightRenderNode* lightNode = (LightRenderNode*)node;

				lights.push_back(lightNode->getLight());
			}

			_shader->updateLightUniformsForwardRendering(lights);

			_shader->updateCameraUniforms(_renderParams.getGlobalParam_GlobalRenderingCamera());

			_shader->setMesh(_mesh);

			_shader->setModelTexture(_texture);

			_shader->updateMaterialPassUniforms(_pass);

			_shader->updateModelUniforms(_renderParams.getPerNodeParam_Transform());

			_shader->updateGPU();
		}
		else {

			_shader->updateCameraUniforms(_renderParams.getGlobalParam_GlobalRenderingCamera());

			_shader->setMesh(_mesh);

			_shader->setModelTexture(_texture);

			_shader->updateMaterialPassUniforms(_pass);

			_shader->updateModelUniforms(_renderParams.getPerNodeParam_Transform());

			_shader->updateGPU();

			if (!_renderParams.getPerNodeParam_DepthTestEnableState()) {

				_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
				_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);
				_shader->getPipeline()->setBlendState(BLEND_STATE::PASS_BLENDING);

			}
			_shader->execute(_mesh->numIndices);

			_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);
			_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
			_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
		}

		_isVisible = false;
	}
}
