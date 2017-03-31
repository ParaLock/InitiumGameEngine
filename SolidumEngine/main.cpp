#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\window.h"

#include "Solidum\EntityFramework\Components\include\CameraComponent.h"

#include "Solidum\EngineCore\include\EngineInstance.h"

#include "Solidum\ResourceFramework\include\ResourceManagerPool.h"

#include "Solidum\EntityFramework\Components\include\MoveComponent.h"
#include "Solidum\EntityFramework\Components\include\LightComponent.h"
#include "Solidum\EntityFramework\Components\include\MeshComponent.h"
#include "Solidum\EntityFramework\Components\include\SkydomeWeatherComponent.h"
#include "Solidum\EntityFramework\Components\include\OrbitComponent.h"
#include "Solidum\EntityFramework\Components\include\SunMoonLightingComponent.h"
#include "Solidum\GraphicsRendering\RenderNode\include\ShadowGenRenderNode.h"

#include "Solidum\InputHandling\include\InputHandler.h"

#include "Solidum\EntityFramework\Entity\include\Entity.h"

#include "Solidum\WorldSimulation\include\World.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	AllocConsole();

	freopen("CONOUT$", "w", stdout);

	windowConfigBlock windowConfig;

	windowConfig.hInstance = hInstance;
	windowConfig.nCmdShow = nCmdShow;

	windowConfig.screen_height = 700;
	windowConfig.screen_width = 1024;

	window *myWindow = new window(&windowConfig);

	EngineInstance *solidum = new EngineInstance(myWindow);

	World* world = new World;

	ResourceManagerPool* resManagerPool = solidum->getResourceManagerPool();

	//** RESOURCE LOADING **//
	GPUPipeline* pipelineResourceInit = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/PipelineResourceINIT.solPipe"), "pipeline_res_init", false)->getCore<GPUPipeline>();

	GPUPipeline* shadowMapGenPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/ShadowMapGenPipeline.solPipe"), "shadow_map_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredRenderingPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/deferredPipeline.solPipe"), "deferred_geometry_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredPointLightsPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/deferredLightingPipeline.solPipe"), "deferred_point_light_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredDirectionalLightsPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/deferredLightingPipeline.solPipe"), "deferred_directional_light_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* forwardRenderingPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/forwardRendering/basicShaders/forwardPipeline.solPipe"), "forward_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* skyRenderingPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/skyPipeline.solPipe"), "sky_pipeline_state", false)->getCore<GPUPipeline>();

	//GPUPipeline* forwardRenderingEndscenePipelineState = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
	//	(L"./res/Pipelines/forwardRendering/basicShaders/endScene_pipeline.solPipe", GraphicsCore::getInstance()->getPipelineCommandQueue()), "endscene_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredRenderingEndscenePipelineState = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredRendering/basicShaders/endScene_pipeline.solPipe"), "endscene_pipeline_state", false)->getCore<GPUPipeline>();

	Light* sunLight = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(LIGHT_TYPE::DIRECTIONAL_LIGHT), "sun", false)->getCore<Light>();

	Light* moonLight = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(LIGHT_TYPE::DIRECTIONAL_LIGHT), "moon", false)->getCore<Light>();

	Light* pointLight1 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(LIGHT_TYPE::POINT_LIGHT), "pointLight1", false)->getCore<Light>();

	Light* pointLight2 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(LIGHT_TYPE::POINT_LIGHT), "pointLight2", false)->getCore<Light>();

	Light* pointLight3 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(LIGHT_TYPE::POINT_LIGHT), "pointLight3", false)->getCore<Light>();

	//mesh* hammerMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
	//	(L"./res/Meshes/hammer2.obj", resManagerPool), "hammer_mesh", false)->getCore<mesh>();

	mesh* cubeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/cube.obj", resManagerPool), "cube_mesh", false)->getCore<mesh>();
	
	mesh* planeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/plane.obj", resManagerPool), "plane_mesh", false)->getCore<mesh>();

	mesh* skydomeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/skydome.obj", resManagerPool), "sky_mesh", false)->getCore<mesh>();

	Texture* grassTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/diffuse/grass.png"), "grass_tex", false)->getCore<Texture>();

	Texture* woodTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/diffuse/Wood.png"), "wood_tex", false)->getCore<Texture>();

	Texture* metalTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/diffuse/metal.png"), "metal_tex", false)->getCore<Texture>();

	Texture* bricksTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/diffuse/grey_bricks.png"), "bricks_tex", false)->getCore<Texture>();

	Texture* bricksNormalMap = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/normals/bricks_normal.bmp"), "bricks_normal_map", false)->getCore<Texture>();

	Texture* skydomeCubeMap = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/cubemaps/sunsetcube1024.dds"), "cube_map", false)->getCore<Texture>();

	Shader* deferredRenderingShaderWNormalMapping = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/deferredShaderWNormalMapping.hlsl", SHADER_RENDER_TYPE::DEFERRED_RENDERING), "deferred_geometry_shader_normal_mapping", false)->getCore<Shader>();

	Shader* deferredRenderingShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/deferredShader.hlsl", SHADER_RENDER_TYPE::DEFERRED_RENDERING), "deferred_geometry_shader", false)->getCore<Shader>();

	Shader* deferredRenderingDirectionalLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/directionalLightShader.hlsl", SHADER_RENDER_TYPE::DEFERRED_RENDERING_LIGHT), "directional_light_shader", false)->getCore<Shader>();

	Shader* deferredRenderingPointLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/pointLightShader.hlsl", SHADER_RENDER_TYPE::DEFERRED_RENDERING_LIGHT), "point_light_shader", false)->getCore<Shader>();

	Shader* skydomeShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/skyShader.hlsl", SHADER_RENDER_TYPE::SKYBOX_RENDERING), "sky_shader", false)->getCore<Shader>();

	Shader* shadowMapGenShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredRendering/basicShaders/deferredDepthMapGenShader.hlsl", SHADER_RENDER_TYPE::SHADOW_MAP_RENDERING), "shadow_map_gen_shader", false)->getCore<Shader>();

	solidum->getGraphicsSubsystem()->registerDefaultShader(DEFAULT_SHADER_TYPE::DEFAULT_MESH, deferredRenderingShader);
	solidum->getGraphicsSubsystem()->registerDefaultShader(DEFAULT_SHADER_TYPE::DEFAULT_LIGHT, deferredRenderingPointLightShader);

	//shadowMapGenShader->attachPipeline(shadowMapGenPipeline);

	//Shader* forwardRenderingShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
	//	(L"./res/Shaders/forwardRendering/forwardRendering.hlsl", SHADER_RENDER_TYPE::FORWARD_RENDERING), "forward_rendering_shader", false)->getCore<Shader>();

	//forwardRenderingShader->attachPipeline(forwardRenderingPipeline);

	deferredRenderingDirectionalLightShader->attachPipeline(deferredDirectionalLightsPipeline);
	deferredRenderingPointLightShader->attachPipeline(deferredPointLightsPipeline);

	skydomeShader->attachPipeline(skyRenderingPipeline);

	Material* brickMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(), "brickMaterial", false)->getCore<Material>();

	brickMaterial->createPass("basicPhongWSpecular", deferredRenderingShaderWNormalMapping, deferredRenderingPipeline);
	
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularIntensity(5.5f);
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularPower(20.0f);

	brickMaterial->getPass("basicPhongWSpecular")->setNormalTexture(bricksNormalMap);
	
	Material* woodMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(), "woodMaterial", false)->getCore<Material>();

	woodMaterial->createPass("basicPhongWSpecular", deferredRenderingShader, deferredRenderingPipeline);

	woodMaterial->getPass("basicPhongWSpecular")->setSpecularColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	woodMaterial->getPass("basicPhongWSpecular")->setSpecularIntensity(0.002f);
	woodMaterial->getPass("basicPhongWSpecular")->setSpecularPower(0.002f);

	KEY_FUNCTION_MAP* moveKeyConfig1 = new KEY_FUNCTION_MAP;
	KEY_FUNCTION_MAP* moveKeyConfig2 = new KEY_FUNCTION_MAP;

	moveKeyConfig1->insert({ KEY_MAP::UP, MOVE_FUNCTION::MOVE_UP});
	moveKeyConfig1->insert({ KEY_MAP::DOWN, MOVE_FUNCTION::MOVE_DOWN });
	moveKeyConfig1->insert({ KEY_MAP::LEFT, MOVE_FUNCTION::MOVE_LEFT });
	moveKeyConfig1->insert({ KEY_MAP::RIGHT, MOVE_FUNCTION::MOVE_RIGHT });

	moveKeyConfig2->insert({ KEY_MAP::I, MOVE_FUNCTION::MOVE_UP });
	moveKeyConfig2->insert({ KEY_MAP::K, MOVE_FUNCTION::MOVE_DOWN });
	moveKeyConfig2->insert({ KEY_MAP::J, MOVE_FUNCTION::MOVE_LEFT });
	moveKeyConfig2->insert({ KEY_MAP::L, MOVE_FUNCTION::MOVE_RIGHT });

	//** RESOURCE LOADING DONE **//

	ResourceManagerPool::getInstance()->getResourceManagerSpecific<LightManager>("LightManager")->setLightShader(LIGHT_TYPE::DIRECTIONAL_LIGHT, deferredRenderingDirectionalLightShader);
	ResourceManagerPool::getInstance()->getResourceManagerSpecific<LightManager>("LightManager")->setLightShader(LIGHT_TYPE::POINT_LIGHT, deferredRenderingPointLightShader);

	sunLight->setColor(Vector4f(0.5f, 0.5f, 0.5f, 0.5f));
	sunLight->setDirection(Vector3f(-5.0f, 5.0f, -5.0f));
	sunLight->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	sunLight->setIntensity(0.5f);

	pointLight1->setColor(Vector4f(0.5f, 2.5f, 0.5f, 0.5f));
	pointLight1->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight1->setPosition(Vector3f(4,4,4));
	pointLight1->setIntensity(5.0f);

	pointLight1->setAttenuationLinear(0);
	pointLight1->setAttenuationExponent(1);
	pointLight1->setAttenuationConstant(0);

	pointLight1->setRange(60.5f);

	pointLight2->setColor(Vector4f(0.5f, 0.5f, 2.5f, 0.5f));
	pointLight2->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight2->setPosition(Vector3f(9.0f, 9.0f, 9.0f));
	pointLight2->setIntensity(5.0f);

	pointLight2->setAttenuationLinear(0);
	pointLight2->setAttenuationExponent(1);
	pointLight2->setAttenuationConstant(0);

	pointLight2->setRange(60.5f);

	pointLight3->setColor(Vector4f(2.5f, 0.5f, 0.5f, 0.5f));
	pointLight3->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight3->setPosition(Vector3f(0, 0, 0));
	pointLight3->setIntensity(5.0f);

	pointLight3->setAttenuationLinear(0);
	pointLight3->setAttenuationExponent(1);
	pointLight3->setAttenuationConstant(0);

	pointLight3->setRange(60.5f);

	Entity* globalWorldLighting = new Entity();
	globalWorldLighting->addComponent(new SunMoonLightingComponent(sunLight, moonLight, 0.1f));

	Entity* sun = new Entity();
	sun->addComponent(new LightComponent(sunLight, 0));


	Entity* pointLight1Entity = new Entity();

	pointLight1Entity->addComponent(new MoveComponent(Vector3f(4.0f, 0.01f, -1.8f), 0.5, false, moveKeyConfig2));
	pointLight1Entity->addComponent(new LightComponent(pointLight1, 0));

	Entity* pointLight2Entity = new Entity();

	pointLight2Entity->addComponent(new MoveComponent(Vector3f(0.2f, 0.01f, -5.0f), 0.5, false, moveKeyConfig1));
	pointLight2Entity->addComponent(new LightComponent(pointLight2, 0));

	Entity* pointLight3Entity = new Entity();

	pointLight3Entity->addComponent(new MeshComponent(cubeMesh, woodTex, woodMaterial, 0));
	pointLight3Entity->addComponent(new MoveComponent(Vector3f(-0.2f, 0.01f, 8.0f), 0.5, false, moveKeyConfig1));
	pointLight3Entity->addComponent(new LightComponent(pointLight3, 0));

	Entity* hammer = new Entity();

	hammer->addComponent(new MeshComponent(cubeMesh, metalTex, brickMaterial, 0));

	Entity* cube = new Entity();

	cube->addComponent(new MoveComponent(Vector3f(0, 5.0f, -3.0f), 0.5, true, moveKeyConfig1));
	cube->addComponent(new MeshComponent(cubeMesh, woodTex, woodMaterial, 0));

	Entity* plane = new Entity();

	plane->addComponent(new MoveComponent(Vector3f(0, -3.5, 0), 0.5, false, moveKeyConfig1));
	plane->addComponent(new MeshComponent(planeMesh, bricksTex, brickMaterial, 0));

	Entity* camera = new Entity();

	camera->addComponent(new CameraComponent(0.1f, 1000.0f));

	Entity* sky = new Entity();

	sky->addComponent(new SkydomeWeatherComponent(skydomeShader, skydomeCubeMap, skydomeMesh,
		(CameraComponent*)camera->getComponentsByType(COMPONENT_TYPE::CAMERA_COMPONENT)->front(),
		Vector4f(0.1f, 0.1f, 0.1f, 1.0f), Vector4f(0.1f, 0.1f, 0.1f, 1.0f), 0));

	//Create Shadow generator
	//solidum->getGraphicsSubsystem()->getRenderNodeTree()->
	//	addNode(new ShadowGenRenderNode(shadowMapGenShader), 2222);

	hammer->addChild(pointLight1Entity);

	world->addPrimaryCamera(camera, 0000);
	
	world->addEntity(sun, 3333);
	world->addEntity(pointLight2Entity, 0001);
	world->addEntity(pointLight3Entity, 0010);
	world->addEntity(globalWorldLighting, 1111);
	world->addEntity(hammer, 0011);
	world->addEntity(plane, 0100);
	world->addEntity(sky, 0101);
	world->addEntity(cube, 0110);

	solidum->loadWorld(world);

	solidum->getGraphicsSubsystem()->setEndFrameHandler(deferredRenderingEndscenePipelineState);

	solidum->start();

	myWindow->destroyWindow();
}

