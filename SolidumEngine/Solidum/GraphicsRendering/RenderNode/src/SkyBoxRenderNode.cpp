#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode(IShader * shader, Vector4f apexColor, Vector4f centerColor, uint64_t id)
{
	_id = id;

	_shader = shader;

	_skydomeApexColor = apexColor;
	_skydomeCenterColor = centerColor;

	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

bool SkyBoxRenderNode::isRenderViable()
{
	if (!_renderParams.getPerNodeParam_isVisible())
		return false;
	if (_renderParams.getPerNodeParam_Mesh() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_RenderCamera() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_MeshTexture() == nullptr)
		return false;

	return true;
}

void SkyBoxRenderNode::render()
{
	if (isRenderViable()) {

		_skydomeApexColor = _renderParams.getPerNodeParam_skydomeApexColor();
		_skydomeCenterColor = _renderParams.getPerNodeParam_skydomeCenterColor();

		mesh* _sphereMesh = _renderParams.getPerNodeParam_Mesh();
		Texture* _cubeTex = _renderParams.getPerNodeParam_MeshTexture();
		CameraComponent* cam = _renderParams.getPerNodeParam_RenderCamera();

		Vector3f eyePos = cam->getPos();
		Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
		Matrix4f view = Matrix4f::transpose(cam->getViewMatrix());
		Matrix4f projection = Matrix4f::transpose(cam->getProjectionMatrix());

		_wvp = t * (view * projection);

		GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
			new ShaderUpdateUniformCommand(&_wvp, "cbuff_skydomeWorldViewProj", _shader));

		GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
			new ShaderUpdateUniformCommand(&_skydomeApexColor, "cbuff_skydomeApexColor", _shader));

		GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
			new ShaderUpdateUniformCommand(&_skydomeCenterColor, "cbuff_skydomeCenterColor", _shader));

		//Resource Hooks must be set in immediate context
		_shader->setMesh(_sphereMesh);
		_shader->setMiscResourceHook(_cubeTex, "sky_tex");

		GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
			new ShaderSyncUniforms(_shader));

		_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
		_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
		_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

		_shader->execute(_sphereMesh->numIndices);
	}
}
