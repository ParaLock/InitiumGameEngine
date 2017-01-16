#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"

#include "Solidum\EngineCore\include\EngineInstance.h"

#include "Solidum\ResourceManagement\include\ResourceManagerPool.h"

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
		(0, 9.0f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "metalMaterial")->getCore<Material>();

	Material* woodMaterial = resManagerPool->getResourceManager("MaterialManager")->createResource(&MaterialBuilder
		(1, 0.0f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)), "woodMaterial")->getCore<Material>();

	SolidumObject* cube = resManagerPool->getResourceManager("SolidumObjectManager")->createResource(&SolidumObjectBuilder
		(), "solidumCube")->getCore<SolidumObject>();

	SolidumObject* plane = resManagerPool->getResourceManager("SolidumObjectManager")->createResource(&SolidumObjectBuilder
		(), "solidumPlane")->getCore<SolidumObject>();

	SolidumObject* hammer = resManagerPool->getResourceManager("SolidumObjectManager")->createResource(&SolidumObjectBuilder
		(), "solidumHammer")->getCore<SolidumObject>();

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

	cube->attachMesh(cubeMesh);
	cube->attachMaterial(woodMaterial);
	cube->attachShader(deferredShader);
	cube->attachTexture(woodTex);
	cube->getTransform()->setPos(Vector3f(0, -2.0f, -3.0f));

	hammer->attachMesh(hammerMesh);
	hammer->attachShader(deferredShader);
	hammer->attachMaterial(metalMaterial);
	hammer->attachTexture(metalTex);
	hammer->getTransform()->setPos(Vector3f(0, 0, 0));

	plane->attachMesh(planeMesh);
	plane->attachShader(deferredShader);
	plane->attachMaterial(metalMaterial);
	plane->attachTexture(metalTex);
	plane->getTransform()->setPos(Vector3f(0, -3.5, 0));

	dirLight1->setColor(Vector4f(0.5f, 1.5f, 0.5f, 0.5f));
	dirLight1->setDirection(Vector3f(0.0f, 0.0f, 9.0f));
	dirLight1->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	dirLight1->setIntensity(0.0f);

	dirLight1->attachShader(directionalLightShader);

	pointLight1->setColor(Vector4f(0.5f, 2.5f, 0.5f, 0.5f));
	pointLight1->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight1->setPosition(Vector3f(-0.1f, 0.01f, 0.5f));
	pointLight1->setIntensity(0.2f);

	pointLight1->setAttenuationLinear(0);
	pointLight1->setAttenuationExponent(1);
	pointLight1->setAttenuationConstant(0);

	pointLight1->setRange(8.5f);

	pointLight1->attachShader(pointLightShader);

	pointLight2->setColor(Vector4f(0.5f, 0.5f, 2.5f, 0.5f));
	pointLight2->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight2->setPosition(Vector3f(0.2f, 0.01f, -0.1f));
	pointLight2->setIntensity(0.2f);

	pointLight2->setAttenuationLinear(0);
	pointLight2->setAttenuationExponent(1.0f);
	pointLight2->setAttenuationConstant(0);

	pointLight2->setRange(8.5f);

	pointLight2->attachShader(pointLightShader);

	pointLight3->setColor(Vector4f(3.5f, 0.5f, 0.5f, 0.5f));
	pointLight3->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight3->setPosition(Vector3f(-0.2f, 0.01f, -0.5f));
	pointLight3->setIntensity(0.1f);

	pointLight3->setAttenuationLinear(0);
	pointLight3->setAttenuationExponent(1.6f);
	pointLight3->setAttenuationConstant(0);

	pointLight3->setRange(8.5f);

	pointLight3->attachShader(pointLightShader);

	//solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueLight(dirLight1);
	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueLight(pointLight1);
	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueLight(pointLight2);
	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueLight(pointLight3);

	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueSoldiumObject(cube);
	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueSoldiumObject(hammer);
	solidum->getGraphicsSubsystem()->getRenderQueue()->enqueueSoldiumObject(plane);

	camera* myCam = solidum->getGraphicsSubsystem()->getPrimaryCamera();

	while (myWindow->running) {

		myWindow->pollWin32Events();

		myCam->cameraMouseLook();

		if (GetAsyncKeyState('W')) {
			myCam->cameraMove("forward", 5.0f);
		}
		if (GetAsyncKeyState('S')) {
			myCam->cameraMove("backward", 5.0f);
		}
		if (GetAsyncKeyState('A')) {
			myCam->cameraMove("left", 5.0f);
		}
		if (GetAsyncKeyState('D')) {
			myCam->cameraMove("right", 5.0f);
		}

		if (GetAsyncKeyState(VK_ESCAPE)) {

			myWindow->running = false;
		}

		myCam->Update();

		solidum->getGraphicsSubsystem()->RenderAll();

		endscenePipelineState->executePass(NULL);
	}
	myWindow->destroyWindow();
}

