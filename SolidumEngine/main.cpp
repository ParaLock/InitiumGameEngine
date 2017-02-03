#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"

#include "Solidum\EngineCore\include\EngineInstance.h"

#include "Solidum\ResourceFramework\include\ResourceManagerPool.h"

#include "Solidum\EntityFramework\Components\include\MoveComponent.h"
#include "Solidum\EntityFramework\Components\include\LightComponent.h"
#include "Solidum\EntityFramework\Components\include\MeshComponent.h"

#include "Solidum\InputHandling\include\InputHandler.h"

#include "Solidum\EntityFramework\Entity\include\Entity.h"

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
	windowAccessor::initAccessor(myWindow);

	EngineInstance *solidum = new EngineInstance(myWindow);

	ResourceManagerPool* resManagerPool = solidum->getResourceManagerPool();

	//** RESOURCE INITIALIZATION **//

	GPUPipeline* endscenePipelineState = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/endScene_pipeline.solPipe", resManagerPool), "endscene_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredPipeline.solPipe", resManagerPool), "deferred_pipeline_state", false)->getCore<GPUPipeline>();

	GPUPipeline* deferredLightingPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredLightingPipeline.solPipe", resManagerPool), "deferred_lighting_pipeline_state", false)->getCore<GPUPipeline>();

	mesh* hammerMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/hammer2.obj", resManagerPool), "hammer_mesh", false)->getCore<mesh>();

	mesh* cubeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/cube.obj", resManagerPool), "cube_mesh", false)->getCore<mesh>();
	
	mesh* planeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/plane.obj", resManagerPool), "plane_mesh", false)->getCore<mesh>();

	mesh* orthoMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"gen_ortho_window_mesh", solidum->getResourceManagerPool()), "orthoMesh", false)->getCore<mesh>();

	Texture* grassTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/grass.png"), "grass_tex", false)->getCore<Texture>();

	Texture* woodTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/Wood.png"), "wood_tex", false)->getCore<Texture>();

	Texture* metalTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/metal.png"), "metal_tex", false)->getCore<Texture>();

	Shader* deferredShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredShader.hlsl", resManagerPool), "deferred_geometry_shader", false)->getCore<Shader>();

	Shader* directionalLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/directionalLightShader.hlsl", resManagerPool), "directional_light_shader", false)->getCore<Shader>();

	Shader* pointLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/pointLightShader.hlsl", resManagerPool), "point_light_shader", false)->getCore<Shader>();

	Material* metalMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(0, 5.5f, 20.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "metalMaterial", false)->getCore<Material>();

	Material* woodMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(1, 0.002f, 0.002f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "woodMaterial", false)->getCore<Material>();

	Light* dirLight1 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "dirLight1", false)->getCore<Light>();

	Light* pointLight1 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight1", false)->getCore<Light>();

	Light* pointLight2 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight2", false)->getCore<Light>();

	Light* pointLight3 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight3", false)->getCore<Light>();

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

	//** RESOURCE INIT DONE **//

	Entity* ROOT_ENTITY = new Entity();

	deferredShader->attachPipeline(deferredPipeline);
	directionalLightShader->attachPipeline(deferredLightingPipeline);
	pointLightShader->attachPipeline(deferredLightingPipeline);


	dirLight1->setColor(Vector4f(1.5f, 2.5f, 1.5f, 1.5f));
	dirLight1->setDirection(Vector3f(0.0f, 0.0f, 9.0f));
	dirLight1->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	dirLight1->setIntensity(0.0f);

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

	pointLight1->attachShader(pointLightShader);
	pointLight2->attachShader(pointLightShader);
	pointLight3->attachShader(pointLightShader);

	dirLight1->attachShader(directionalLightShader);

	pointLightShader->setMesh(orthoMesh);
	directionalLightShader->setMesh(orthoMesh);

	Entity* hammer = new Entity();

	hammer->addComponent(new MoveComponent(Vector3f(0, 0, 0), 0.5, true, moveKeyConfig1));
	hammer->addComponent(new MeshComponent(hammerMesh, metalTex, metalMaterial, deferredShader));

	Entity* cube = new Entity();

	cube->addComponent(new MoveComponent(Vector3f(0, 5.0f, -3.0f), 0.5, false, moveKeyConfig1));
	cube->addComponent(new MeshComponent(cubeMesh, woodTex, woodMaterial, deferredShader));

	Entity* plane = new Entity();

	plane->addComponent(new MoveComponent(Vector3f(0, -3.5, 0), 0.5, false, moveKeyConfig1));
	plane->addComponent(new MeshComponent(planeMesh, metalTex, metalMaterial, deferredShader));

	Entity* dirLightEntity = new Entity();

	dirLightEntity->addComponent(new LightComponent(dirLight1));

	Entity* pointLight1Entity = new Entity();

	pointLight1Entity->addComponent(new MoveComponent(Vector3f(4.0f, 0.01f, -1.8f), 0.5, true, moveKeyConfig2));
	pointLight1Entity->addComponent(new LightComponent(pointLight1));

	Entity* pointLight2Entity = new Entity();

	pointLight2Entity->addComponent(new MoveComponent(Vector3f(0.2f, 0.01f, -5.0f), 0.5, false, moveKeyConfig1));
	pointLight2Entity->addComponent(new LightComponent(pointLight2));

	Entity* pointLight3Entity = new Entity();

	pointLight3Entity->addComponent(new MeshComponent(cubeMesh, woodTex, woodMaterial, deferredShader));
	pointLight3Entity->addComponent(new MoveComponent(Vector3f(-0.2f, 0.01f, 8.0f), 0.5, false, moveKeyConfig1));
	pointLight3Entity->addComponent(new LightComponent(pointLight3));

	camera* myCam = solidum->getGraphicsSubsystem()->getPrimaryCamera();

	InputHandler* inputHandler = resManagerPool->getResourceManager("InputHandlerManager")->
		getResource("InputHandler")->getCore<InputHandler>();

	hammer->addChild(pointLight1Entity);
	hammer->addChild(cube);

	ROOT_ENTITY->addChild(hammer);
	ROOT_ENTITY->addChild(plane);
	ROOT_ENTITY->addChild(pointLight2Entity);
	ROOT_ENTITY->addChild(pointLight3Entity);
	//ROOT_ENTITY->addChild(dirLightEntity);

	while (myWindow->running) {

		myWindow->pollWin32Events();

		if (GetAsyncKeyState(VK_ESCAPE)) {

			myWindow->running = false;
		}

		inputHandler->update();

		myCam->Update();

		ROOT_ENTITY->update();

		solidum->getGraphicsSubsystem()->RenderAll();

		endscenePipelineState->executePass(NULL);
	}
	myWindow->destroyWindow();
}

