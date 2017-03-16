#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode(IShader * shader, Texture * tex, mesh * skydome, CameraComponent* cam)
{
	_shader = shader;
	_cubeTex = tex;
	_skydomeMesh = skydome;
	_cam = cam;

	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

void SkyBoxRenderNode::render()
{
	Vector3f eyePos = _cam->getPos();
	Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
	Matrix4f view = Matrix4f::transpose(_cam->getViewMatrix());
	Matrix4f projection = Matrix4f::transpose(_cam->getProjectionMatrix());

    _wvp = t * (view * projection);


	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_wvp, "cbuff_skydomeWorldViewProj", _shader));

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
