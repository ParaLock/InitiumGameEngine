#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshFactory.h"
#include "Solidum\GraphicsRendering\Directx11Rendering\dxDevice\include\dxDevice.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshLoaderOBJ.h"
#include "Solidum\GraphicsRendering\Shaders\include\ShaderFactory.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"
#include "Solidum\GraphicsRendering\Renderer3D\include\IRenderer3D.h"
#include "Solidum\GraphicsRendering\Directx11Rendering\dxRenderer3D\include\dxRenderer3D.h"

#include "Solidum\GraphicsRendering\Lights\include\LightFactory.h"
#include "Solidum\GraphicsRendering\Textures\include\TextureFactory.h"


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	windowConfigBlock windowConfig;

	windowConfig.hInstance = hInstance;
	windowConfig.nCmdShow = nCmdShow;

	windowConfig.screen_height = 700;
	windowConfig.screen_width = 1024;

	window *myWindow = new window(&windowConfig);
	windowAccessor::initAccessor(myWindow);


	camera *myCam = new camera(0.1f, 1000.0f);

	dxDeviceManager *dxManager = new dxDeviceManager();

	dxConfigBlock dxConfig;

	dxConfig.swapchain.Height = 700;
	dxConfig.swapchain.Width = 1024;
	dxConfig.swapchain.OutputWindow = myWindow->hWnd;
	
	dxManager->dxCreateDev(&dxConfig);

	dxDeviceAccessor::initAccessor(dxManager);

	IRenderer3D* myRenderer = new dxRenderer3D();

	IShader *deferredShader = ShaderFactory::createShader(L"deferredShader.fx", DXSHADER_TYPE_DEFERRED, "deferred_shader");
	IShader *directionalLightShader = ShaderFactory::createShader(L"DirectionalLight.fx", DXSHADER_TYPE_DirectionalLight, "dir_light_shader");
	
	LightFactory::registerShaderToLight(LIGHT_TYPE_DIRECTIONAL, "dir_light_shader");

	Light *dirLight = LightFactory::createLight(LIGHT_TYPE_DIRECTIONAL, "dir_light");

	Light *dirLight2 = LightFactory::createLight(LIGHT_TYPE_DIRECTIONAL, "dir_light2");

	std::shared_ptr<meshLoader> objLdr = std::shared_ptr<meshLoader>(new meshLoaderOBJ());

	mesh *hammerMesh = meshFactory::createMesh(L"hammer2.obj", objLdr, "hammer_mesh");
	mesh* cubeMesh = meshFactory::createMesh(L"cube.obj", objLdr, "cube_mesh");

	ITexture* grassTex = TextureFactory::createTexture(L"grass.png", DXTEXTURE, "grass_texture");
	ITexture* woodTex = TextureFactory::createTexture(L"Wood.png", DXTEXTURE, "wood_texture");


	D3DXMATRIX OBJSpecificTransform;

	D3DXMATRIX placeHolder, GStage_projectionMatrix, GStage_viewMatrix, GStage_worldMatrix,
		GStage_OBJSpecificMatrix;

	D3DXMATRIX LStage_projectionMatrix, LStage_viewMatrix, LStage_worldMatrix;


	std::shared_ptr<std::vector<IRenderTarget*>> deferredRenderTargets = RenderTargetFactory::createRenderTargets(2);

	deferredRenderTargets->at(0)->parentShaderType = PARENT_SHADER_TYPE_PIXEL;
	deferredRenderTargets->at(1)->parentShaderType = PARENT_SHADER_TYPE_PIXEL;

	deferredRenderTargets->at(0)->resSlot = 0;
	deferredRenderTargets->at(1)->resSlot = 1;

	myRenderer->addGBuffer(deferredRenderTargets->at(0));
	myRenderer->addGBuffer(deferredRenderTargets->at(1));

	D3DXVECTOR4 *lightColor = new D3DXVECTOR4(2.0f, 2.0f, 2.0f, 2.0f);
	D3DXVECTOR3 *lightPos = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 *lightDirection = new D3DXVECTOR3(0.0f, 0.0f, 9.0f);

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

		D3DXMatrixTranslation(&OBJSpecificTransform, 0.0f, 0.0f, 0.0f);

		GStage_projectionMatrix = myCam->getProjectionMatrix();
		GStage_viewMatrix = myCam->getViewMatrix();
		GStage_worldMatrix = myCam->getWorldMatrix();
		GStage_OBJSpecificMatrix = OBJSpecificTransform;

		D3DXMatrixTranspose(&GStage_worldMatrix, &GStage_worldMatrix);
		D3DXMatrixTranspose(&GStage_viewMatrix, &GStage_viewMatrix);
		D3DXMatrixTranspose(&GStage_projectionMatrix, &GStage_projectionMatrix);

		LStage_projectionMatrix = myCam->getOrtho();
		LStage_viewMatrix = myCam->getStartCamView();
		LStage_worldMatrix = myCam->getWorldMatrix();

		D3DXMatrixTranspose(&LStage_worldMatrix, &LStage_worldMatrix);
		D3DXMatrixTranspose(&LStage_viewMatrix, &LStage_viewMatrix);


		dirLight->updateVar("lightColor", lightColor);
		dirLight->updateVar("lightPos", lightPos);
		dirLight->updateVar("lightDirection", lightDirection);

		dirLight->updateVar("worldMatrix", LStage_worldMatrix);
		dirLight->updateVar("viewMatrix", LStage_viewMatrix);
		dirLight->updateVar("projectionMatrix", LStage_projectionMatrix);

		deferredShader->updateVar("worldMatrix", GStage_worldMatrix);
		deferredShader->updateVar("viewMatrix", GStage_viewMatrix);
		deferredShader->updateVar("projectionMatrix", GStage_projectionMatrix);
		deferredShader->updateVar("OBJSpecificMatrix", GStage_OBJSpecificMatrix);

		deferredShader->updateGPU();
		directionalLightShader->updateGPU();

		deferredShader->attachTex(grassTex);
		myRenderer->RenderMesh(cubeMesh, deferredShader);

		deferredShader->attachTex(woodTex);
		myRenderer->RenderMesh(hammerMesh, deferredShader);

		myRenderer->RenderLight(dirLight);

		myRenderer->swapFrame();

		myRenderer->clearGBuffers(0.0f, 0.0f, 0.0f, 0.0f);
		myRenderer->clearFrameBuffer(0.0f, 0.0f, 0.0f, 0.0f);
		myRenderer->clearZBuffer();
	}

	myWindow->destroyWindow();

	delete myRenderer;
}

