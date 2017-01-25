#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"

#include "Solidum\EngineCore\include\EngineInstance.h"

#include "Solidum\ResourceFramework\include\ResourceManagerPool.h"

#include "Solidum\EntityFramework\Components\include\MoveComponent.h"
#include "Solidum\EntityFramework\Components\include\GraphicsComponent.h"

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

	GPUPipeline* endscenePipelineState = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/endScene_pipeline.solPipe", resManagerPool), "endscene_pipeline_state")->getCore<GPUPipeline>();

	GPUPipeline* deferredPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredPipeline.solPipe", resManagerPool), "deferred_pipeline_state")->getCore<GPUPipeline>();

	GPUPipeline* deferredLightingPipeline = resManagerPool->getResourceManager("GPUPipelineManager")->createResource(&GPUPipelineBuilder
		(L"./res/Pipelines/deferredLightingPipeline.solPipe", resManagerPool), "deferred_lighting_pipeline_state")->getCore<GPUPipeline>();

	mesh* hammerMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/hammer2.obj", resManagerPool), "hammer_mesh")->getCore<mesh>();

	mesh* cubeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/cube.obj", resManagerPool), "cube_mesh")->getCore<mesh>();
	
	mesh* planeMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"./res/Meshes/plane.obj", resManagerPool), "plane_mesh")->getCore<mesh>();

	mesh* orthoMesh = resManagerPool->getResourceManager("meshManager")->createResource(&meshBuilder
		(L"gen_ortho_window_mesh", solidum->getResourceManagerPool()), "orthoMesh")->getCore<mesh>();

	Texture* grassTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/grass.png"), "grass_tex")->getCore<Texture>();

	Texture* woodTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/Wood.png"), "wood_tex")->getCore<Texture>();

	Texture* metalTex = resManagerPool->getResourceManager("TextureManager")->createResource(&TextureBuilder
		(L"./res/Textures/metal.png"), "metal_tex")->getCore<Texture>();

	Shader* deferredShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/deferredShader.hlsl", resManagerPool), "deferred_geometry_shader")->getCore<Shader>();

	Shader* directionalLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/directionalLightShader.hlsl", resManagerPool), "directional_light_shader")->getCore<Shader>();

	Shader* pointLightShader = resManagerPool->getResourceManager("ShaderManager")->createResource(&ShaderBuilder
		(L"./res/Shaders/pointLightShader.hlsl", resManagerPool), "point_light_shader")->getCore<Shader>();

	Material* metalMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(0, 0.5f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "metalMaterial")->getCore<Material>();

	Material* woodMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(1, 0.0f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "woodMaterial")->getCore<Material>();

	Light* dirLight1 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "dirLight1")->getCore<Light>();

	Light* pointLight1 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight1")->getCore<Light>();

	Light* pointLight2 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight2")->getCore<Light>();

	Light* pointLight3 = resManagerPool->getResourceManager("LightManager")->createResource(&LightBuilder
		(), "pointLight3")->getCore<Light>();

	deferredShader->attachPipeline(deferredPipeline);
	directionalLightShader->attachPipeline(deferredLightingPipeline);
	pointLightShader->attachPipeline(deferredLightingPipeline);

	directionalLightShader->setMesh(orthoMesh);
	pointLightShader->setMesh(orthoMesh);

	dirLight1->setColor(Vector4f(0.5f, 1.5f, 0.5f, 0.5f));
	dirLight1->setDirection(Vector3f(0.0f, 0.0f, 9.0f));
	dirLight1->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	dirLight1->setIntensity(0.0f);

	pointLight1->setColor(Vector4f(0.5f, 2.5f, 0.5f, 0.5f));
	pointLight1->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight1->setPosition(Vector3f(-6.0f, 0.01f, 0.5f));
	pointLight1->setIntensity(5.0f);

	pointLight1->setAttenuationLinear(0);
	pointLight1->setAttenuationExponent(1);
	pointLight1->setAttenuationConstant(0);

	pointLight1->setRange(20.5f);

	pointLight2->setColor(Vector4f(0.5f, 0.5f, 2.5f, 0.5f));
	pointLight2->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight2->setPosition(Vector3f(0.2f, 0.01f, -5.0f));
	pointLight2->setIntensity(5.0f);

	pointLight2->setAttenuationLinear(0);
	pointLight2->setAttenuationExponent(1);
	pointLight2->setAttenuationConstant(0);

	pointLight2->setRange(20.5f);

	pointLight3->setColor(Vector4f(2.5f, 0.5f, 0.5f, 0.5f));
	pointLight3->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight3->setPosition(Vector3f(-0.2f, 0.01f, 8.0f));
	pointLight3->setIntensity(5.0f);

	pointLight3->setAttenuationLinear(0);
	pointLight3->setAttenuationExponent(1);
	pointLight3->setAttenuationConstant(0);

	pointLight3->setRange(20.5f);

	Entity* hammer = new Entity();

	hammer->addComponent(new MoveComponent(Vector3f(0, 0, 0), 0.5, true, hammer->getTransform()));
	hammer->addComponent(new GraphicsComponent("hammer_mesh", "metal_tex", "metalMaterial", "deferred_geometry_shader", "null", hammer->getTransform()));

	Entity* cube = new Entity();

	cube->addComponent(new MoveComponent(Vector3f(0, -2.0f, -3.0f), 0.5, true, cube->getTransform()));
	cube->addComponent(new GraphicsComponent("cube_mesh", "wood_tex", "woodMaterial", "deferred_geometry_shader", "null", cube->getTransform()));

	Entity* plane = new Entity();

	plane->addComponent(new MoveComponent(Vector3f(0, -3.5, 0), 0.5, false, plane->getTransform()));
	plane->addComponent(new GraphicsComponent("plane_mesh", "metal_tex", "metalMaterial", "deferred_geometry_shader", "null", plane->getTransform()));

	Entity* dirLightEntity = new Entity();

	dirLightEntity->addComponent(new GraphicsComponent("orthoMesh", "null", "null", "directional_light_shader", "dirLight1", dirLightEntity->getTransform()));

	Entity* pointLight1Entity = new Entity();

	pointLight1Entity->addComponent(new GraphicsComponent("orthoMesh", "null", "null", "point_light_shader", "pointLight1", nullptr));

	Entity* pointLight2Entity = new Entity();

	pointLight2Entity->addComponent(new GraphicsComponent("orthoMesh", "null", "null", "point_light_shader", "pointLight2", nullptr));

	Entity* pointLight3Entity = new Entity();

	pointLight3Entity->addComponent(new GraphicsComponent("orthoMesh", "null", "null", "point_light_shader", "pointLight3", nullptr));

	camera* myCam = solidum->getGraphicsSubsystem()->getPrimaryCamera();

	InputHandler* inputHandler = resManagerPool->getResourceManager("InputHandlerManager")->
		getResource("InputHandler")->getCore<InputHandler>();

	while (myWindow->running) {

		myWindow->pollWin32Events();

		if (GetAsyncKeyState(VK_ESCAPE)) {

			myWindow->running = false;
		}

		inputHandler->update();

		myCam->Update();

		cube->update();
		hammer->update();
		plane->update();

		pointLight1Entity->update();
		pointLight2Entity->update();
		pointLight3Entity->update();

		endscenePipelineState->executePass(NULL);
	}
	myWindow->destroyWindow();
}

