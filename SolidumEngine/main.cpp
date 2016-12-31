#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\windowAccessor.h"
#include "Solidum\GraphicsRendering\Window\include\window.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshFactory.h"
#include "Solidum\GraphicsRendering\Mesh\include\meshLoaderOBJ.h"
#include "Solidum\GraphicsRendering\Camera\include\camera.h"

#include "Solidum\GraphicsRendering\RenderingCore\include\GraphicsRenderer.h"
#include "Solidum\GraphicsRendering\Shaders\include\ShaderFactory.h"

#include "Solidum\GraphicsRendering\Directx11Rendering\dxDevice\include\dxDeviceAccessor.h"

#include "Solidum\GraphicsRendering\Lights\include\Light.h"
#include "Solidum\GraphicsRendering\Lights\include\LightFactory.h"

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

	std::shared_ptr<meshLoader> objLdr = std::shared_ptr<meshLoader>(new meshLoaderOBJ());

	mesh *hammerMesh = meshFactory::createMesh(L"hammer2.obj", objLdr, "hammer_mesh");
	mesh* cubeMesh = meshFactory::createMesh(L"cube.obj", objLdr, "cube_mesh");
	mesh* orthoWindowMesh = meshFactory::createMesh(L"gen_ortho_window_mesh", nullptr, "window_mesh");

	Shader* deferredShader = ShaderFactory::createShader(L"deferredShader.fx", L"deferred_shader_pipeline.solPipe");
	Shader* dirLightShader = ShaderFactory::createShader(L"DirectionalLight.fx", L"directionalLight_shader_pipeline.solPipe");

	dirLightShader->setMeshBuffers(orthoWindowMesh->getIndexBuff(), orthoWindowMesh->getVertexBuff(), "window_mesh");

	Texture* grassTex = TextureFactory::createTexture();
	Texture* woodTex = TextureFactory::createTexture();

	grassTex->loadImage(L"grass.png");
	woodTex->loadImage(L"Wood.png");

	Light* dirLight1 = new Light();

	dirLight1->attachShader(dirLightShader);

	cubeMesh->setActiveShader(deferredShader);
	cubeMesh->setActiveTexture(grassTex);

	hammerMesh->setActiveShader(deferredShader);
	hammerMesh->setActiveTexture(woodTex);

	D3DXMATRIX OBJSpecificTransform;

	D3DXMATRIX placeHolder, GStage_projectionMatrix, GStage_viewMatrix, GStage_worldMatrix,
		GStage_OBJSpecificMatrix;

	D3DXMATRIX LStage_projectionMatrix, LStage_viewMatrix, LStage_worldMatrix;

	float lightColor[4] = { 2.0f, 2.0f, 2.0f, 2.0f };
	float lightPos[3] = { 0.0f, 0.0f, 0.0f };
	float lightDirection[3] = { 0.0f, 0.0f, 9.0f };

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

		deferredShader->updateCPUGeneralDataVar("worldMatrix", GStage_worldMatrix);
		deferredShader->updateCPUGeneralDataVar("viewMatrix", GStage_viewMatrix);
		deferredShader->updateCPUGeneralDataVar("projectionMatrix", GStage_projectionMatrix);
		deferredShader->updateCPUGeneralDataVar("OBJSpecificMatrix", GStage_OBJSpecificMatrix);

		dirLightShader->updateCPUGeneralDataVar("worldMatrix", LStage_worldMatrix);
		dirLightShader->updateCPUGeneralDataVar("viewMatrix", LStage_viewMatrix);
		dirLightShader->updateCPUGeneralDataVar("projectionMatrix", LStage_projectionMatrix);

		dirLightShader->updateCPUGeneralDataVar("lightDirection", lightDirection);
		dirLightShader->updateCPUGeneralDataVar("lightPos", lightPos);
		dirLightShader->updateCPUGeneralDataVar("lightColor", lightColor);

		dxDeviceAccessor::dxEncapsulator->setViewport("mesh");

		cubeMesh->draw();
		hammerMesh->draw();

		dxDeviceAccessor::dxEncapsulator->setViewport("light");
		dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

		dxDeviceAccessor::dxEncapsulator->dxDevContext->OMSetRenderTargets(1, &dxCore->FrameBufferShaderAccess, dxCore->depthStencil);

		dirLight1->draw();

		dxDeviceAccessor::dxEncapsulator->dxSwapchain->Present(1, 0);

		dxDeviceAccessor::dxEncapsulator->dxDevContext->ClearRenderTargetView(dxDeviceAccessor::dxEncapsulator->FrameBufferShaderAccess, D3DXCOLOR(0, 0, 0, 0));
		dxDeviceAccessor::dxEncapsulator->clearDepthStencil();

	}

	myWindow->destroyWindow();
}

