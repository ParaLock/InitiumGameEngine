#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshFactory.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshLoaderOBJ.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"
#include "Solidum\GraphicsRendering\RenderingCore\include\GraphicsRenderer.h"
#include "Solidum\GraphicsRendering\Shaders\include\ShaderFactory.h"
#include "Solidum\GraphicsRendering\Lights\include\Light.h"
#include "Solidum\GraphicsRendering\Lights\include\LightFactory.h"
#include "Solidum\GraphicsRendering\Material\include\Material.h"

#include "Solidum\EngineCore\SolidumObject\Objects\include\SolidumObject.h"
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

	camera *myCam = new camera(0.1f, 1000.0f);

	GraphicsRenderer* myRenderer = new GraphicsRenderer(SUPPORTED_GRAPHICS_API::DIRECTX11, myWindow);
	myRenderer->attachPrimaryCamera(myCam);

	GPUPipeline* endScene = GPUPipelineFactory::createPipeline(L"endScene_pipeline.solPipe");

	SolidumObject* cube = new SolidumObject();
	SolidumObject* hammer = new SolidumObject();
	SolidumObject* plane = new SolidumObject();

	Material* metalMaterial = new Material(9.0f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f), 0);
	Material* woodMaterial = new Material(0.0f, 0.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f), 1);

	std::shared_ptr<meshLoader> objLdr = std::shared_ptr<meshLoader>(new meshLoaderOBJ());

	mesh *hammerMesh = meshFactory::createMesh(L"hammer2.obj", objLdr, "hammer_mesh");
	mesh* cubeMesh = meshFactory::createMesh(L"cube.obj", objLdr, "cube_mesh");
	mesh* planeMesh = meshFactory::createMesh(L"plane.obj", objLdr, "plane_mesh");
	mesh* orthoWindowMesh = meshFactory::createMesh(L"gen_ortho_window_mesh", nullptr, "window_mesh");

	Shader* deferredShader = ShaderFactory::createShader(L"deferredShader.hlsl", L"deferredPipeline.solPipe");
	Shader* directionalLightShader = ShaderFactory::createShader(L"directionalLightShader.hlsl", L"deferredLightingPipeline.solPipe");
	Shader* pointLightShader = ShaderFactory::createShader(L"pointLightShader.hlsl", L"deferredLightingPipeline.solPipe");

	Texture* grassTex = TextureFactory::createTexture();
	Texture* woodTex = TextureFactory::createTexture();
	Texture* metalTex = TextureFactory::createTexture();

	grassTex->loadImage(L"grass.png");
	woodTex->loadImage(L"Wood.png");
	metalTex->loadImage(L"metal.png");

	metalMaterial->attachMaterialTexture(metalTex, MATERIAL_TEX::PRIMARY_MATERIAL_TEXTURE);
	woodMaterial->attachMaterialTexture(woodTex, MATERIAL_TEX::PRIMARY_MATERIAL_TEXTURE);

	cube->attachMesh(cubeMesh);
	cube->attachMaterial(woodMaterial);
	cube->attachShader(deferredShader);
	cube->getTransform()->setPos(Vector3f(0, -2.0f, -3.0f));

	hammer->attachMesh(hammerMesh);
	hammer->attachShader(deferredShader);
	hammer->attachMaterial(metalMaterial);
	hammer->getTransform()->setPos(Vector3f(0, 0, 0));

	plane->attachMesh(planeMesh);
	plane->attachShader(deferredShader);
	plane->attachMaterial(metalMaterial);
	plane->getTransform()->setPos(Vector3f(0, -3.5, 0));

	Light* dirLight1 = new Light();
	Light* pointLight1 = new Light();
	Light* pointLight2 = new Light();
	Light* pointLight3 = new Light();

	directionalLightShader->setMesh(orthoWindowMesh);
	pointLightShader->setMesh(orthoWindowMesh);

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

	pointLight1->setRange(10.5f);

	pointLight1->attachShader(pointLightShader);

	pointLight2->setColor(Vector4f(0.5f, 0.5f, 2.5f, 0.5f));
	pointLight2->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight2->setPosition(Vector3f(0.2f, 0.01f, -0.1f));
	pointLight2->setIntensity(0.2f);

	pointLight2->setAttenuationLinear(0);
	pointLight2->setAttenuationExponent(1.0f);
	pointLight2->setAttenuationConstant(0);

	pointLight2->setRange(10.5f);

	pointLight2->attachShader(pointLightShader);

	pointLight3->setColor(Vector4f(3.5f, 0.5f, 0.5f, 0.5f));
	pointLight3->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	pointLight3->setPosition(Vector3f(-0.2f, 0.01f, -0.5f));
	pointLight3->setIntensity(0.2f);

	pointLight3->setAttenuationLinear(0);
	pointLight3->setAttenuationExponent(1.0f);
	pointLight3->setAttenuationConstant(0);

	pointLight3->setRange(10.5f);

	pointLight3->attachShader(pointLightShader);

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

		myRenderer->renderSolidumObject(hammer);
		myRenderer->renderSolidumObject(cube);
		myRenderer->renderSolidumObject(plane);

		//myRenderer->renderLight(dirLight1);
		myRenderer->renderLight(pointLight1);
		myRenderer->renderLight(pointLight2);
		myRenderer->renderLight(pointLight3);

		endScene->executePass(NULL);
	}
	myWindow->destroyWindow();
}

