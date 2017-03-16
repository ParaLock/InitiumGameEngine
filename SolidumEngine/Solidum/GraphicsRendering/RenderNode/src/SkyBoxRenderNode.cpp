#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode(IShader * shader, Texture * tex, mesh * skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor)
{
	_shader = shader;
	_cubeTex = tex;
	_skydomeMesh = skydome;
	_cam = cam;

	_skydomeApexColor = apexColor;
	_skydomeCenterColor = centerColor;

	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

void SkyBoxRenderNode::render()
{
	_skydomeApexColor = _renderParams.getPerNodeParam_skydomeApexColor();
	_skydomeCenterColor = _renderParams.getPerNodeParam_skydomeCenterColor();

	Vector3f eyePos = _cam->getPos();
	Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
	Matrix4f view = Matrix4f::transpose(_cam->getViewMatrix());
	Matrix4f projection = Matrix4f::transpose(_cam->getProjectionMatrix());

    _wvp = t * (view * projection);

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_wvp, "cbuff_skydomeWorldViewProj", _shader));

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_skydomeApexColor, "cbuff_skydomeApexColor", _shader));

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_skydomeCenterColor, "cbuff_skydomeCenterColor", _shader));

	//Resource Hooks must be set in immediate context
	_shader->setMesh(_skydomeMesh);
	_shader->setMiscResourceHook(_cubeTex, "sky_tex");

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderSyncUniforms(_shader));

	_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
	_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
	_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

	_shader->execute(_skydomeMesh->numIndices);
}
