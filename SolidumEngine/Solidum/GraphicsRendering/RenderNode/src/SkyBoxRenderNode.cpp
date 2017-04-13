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

		GraphicsCore* gCore = GraphicsCore::getInstance();
		GraphicsCommandPool* commandPool = gCore->getGraphicsCommandPool();

		GraphicsCommand* updateUniform_WVP			= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
		GraphicsCommand* updateUniform_ApexColor	= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
		GraphicsCommand* updateUniform_CenterColor  = commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		GraphicsCommand* syncUniforms				= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

		GraphicsCommand* drawIndexedModel			= commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);
		GraphicsCommand* resetPipeline				= commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);

		syncUniforms->load(std::make_shared<ShaderSyncUniforms::InitData>(_shader));

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

		updateUniform_WVP->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeWorldViewProj", &_wvp), _shader));

		updateUniform_ApexColor->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeApexColor", &_skydomeApexColor), _shader));

		updateUniform_CenterColor->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeCenterColor", &_skydomeCenterColor), _shader));

		drawIndexedModel->load(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, _sphereMesh->numIndices));

		commandList->queueCommand(updateUniform_WVP);

		commandList->queueCommand(updateUniform_ApexColor);

		commandList->queueCommand(updateUniform_CenterColor);

		//Resource Hooks must be set in immediate context
		_shader->setMesh(_sphereMesh);
		_shader->setMiscResourceHook(_cubeTex, "sky_tex");

		commandList->queueCommand(syncUniforms);

		_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
		_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
		_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

		_shader->execute(commandList);

		commandList->queueCommand(drawIndexedModel);
		commandList->queueCommand(resetPipeline);
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);
}
