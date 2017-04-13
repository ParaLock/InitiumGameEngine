#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode()
{
	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

void SkyBoxRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	_wvp = Matrix4f::get_identity();

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;
	_shader = realBuilder->_shader;

	_skydomeApexColor = realBuilder->_apexColor;
	_skydomeCenterColor = realBuilder->_centerColor;

	isLoaded = true;
}

void SkyBoxRenderNode::unload()
{
	isLoaded = false;
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
	GraphicsCommandList* commandList = new GraphicsCommandList();

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

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeWorldViewProj", &_wvp), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeApexColor", &_skydomeApexColor), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeCenterColor", &_skydomeCenterColor), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		//Resource Hooks must be set in immediate context
		_shader->setMesh(_sphereMesh);
		_shader->setMiscResourceHook(_cubeTex, "sky_tex");

		commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_shader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

		_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
		_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
		_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

		_shader->execute(commandList);

		commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, _sphereMesh->numIndices), 
			GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

		commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);
}
