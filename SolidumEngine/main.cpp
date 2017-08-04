#include <windows.h>

#include "Solidum\GraphicsRendering\Window\include\window.h"

#include "Solidum\EntityFramework\Components\include\CameraComponent.h"

#include "Solidum\EngineCore\include\EngineInstance.h"

#include "Solidum\EntityFramework\Components\include\MoveComponent.h"
#include "Solidum\EntityFramework\Components\include\LightComponent.h"
#include "Solidum\EntityFramework\Components\include\MeshComponent.h"
#include "Solidum\EntityFramework\Components\include\SkydomeWeatherComponent.h"
#include "Solidum\EntityFramework\Components\include\OrbitComponent.h"
#include "Solidum\EntityFramework\Components\include\SunMoonLightingComponent.h"
#include "Solidum\EntityFramework\Components\include\ParticleEmitterComponent.h"

#include "Solidum\InputHandling\include\InputHandler.h"

#include "Solidum\EntityFramework\Entity\include\Entity.h"

#include "Solidum\WorldSimulation\include\World.h"

#include "Solidum\GraphicsRendering\RenderDataProcessingLayers\include\FrustumCullingLayer.h"

#include "Plugins\RenderPasses\light_render_pass.h"
#include "Plugins\RenderPasses\mesh_render_pass.h"
#include "Plugins\RenderPasses\particle_render_pass.h"
#include "Plugins\RenderPasses\shadow_map_render_pass.h"
#include "Plugins\RenderPasses\sky_render_pass.h"

#include "Solidum\MemoryManagement\include\SlabCache.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand((unsigned)time(NULL));

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

	world->setBoundingSphere(new BoundingSphere(Vector3f(0,0,0), std::sqrt(2.5 * 2.5 + 4.5 * 4.5)));

	solidum->loadWorld(world);

	ResourceCreator& resCreator = solidum->getResourceCreator();

	//** PLUGIN LOADING... !IN THE FUTURE PLUGINS WILL BE LOADED FROM DLL's! **//
	reg_render_pass__sky(std::bind(&GraphicsCore::registerRenderPass, solidum->getGraphicsSubsystem(), std::placeholders::_1), &resCreator);
	reg_render_pass__light(std::bind(&GraphicsCore::registerRenderPass, solidum->getGraphicsSubsystem(), std::placeholders::_1), &resCreator);
	reg_render_pass__mesh(std::bind(&GraphicsCore::registerRenderPass, solidum->getGraphicsSubsystem(), std::placeholders::_1), &resCreator);
	reg_render_pass__particleEmitter(std::bind(&GraphicsCore::registerRenderPass, solidum->getGraphicsSubsystem(), std::placeholders::_1), &resCreator);
	reg_render_pass__shadowmap(std::bind(&GraphicsCore::registerRenderPass, solidum->getGraphicsSubsystem(), std::placeholders::_1), &resCreator);
	
	//** PLUGING LOADING END **//

	//** RESOURCE LOADING **//

	Renderer* simpleDeferredRenderer = (Renderer*)resCreator.createResourceImmediate<Renderer>(&Renderer::InitData("./res/RenderFlowGraphs/SimpleDeferredRenderFlow.txt", &resCreator),
		"simpleDeferredRenderer", [=](IResource* res) { solidum->getGraphicsSubsystem()->registerRenderer((Renderer*)res); });

	simpleDeferredRenderer->pushGeneralProcessingLayer(std::make_shared<FrustumCullingLayer>());

	Light* sunLight = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::DIRECTIONAL_LIGHT),
		"sun", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });

	Light* moonLight = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::DIRECTIONAL_LIGHT),
		"moon", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });
	
	Light* pointLight1 = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::POINT_LIGHT),
		"pointLight1", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });
	
	Light* pointLight2 = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::POINT_LIGHT),
		"pointLight2", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });
	
	Light* pointLight3 = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::POINT_LIGHT),
		"pointLight3", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });
	
	Light* fireLight = (Light*)resCreator.createResourceImmediate<Light>(&Light::InitData(LIGHT_TYPE::POINT_LIGHT),
		"fire_light", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("LightGroup"), solidum); });
	

	mesh* cubeMesh = (mesh*)resCreator.createResourceImmediate<mesh>(&mesh::InitData(L"./res/Meshes/cube.obj", &resCreator),
		"cube_mesh", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("MeshGroup"), solidum); });
	
	mesh* planeMesh = (mesh*)resCreator.createResourceImmediate<mesh>(&mesh::InitData(L"./res/Meshes/plane.obj", &resCreator),
		"plane_mesh", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("MeshGroup"), solidum); });

	mesh* skydomeMesh = (mesh*)resCreator.createResourceImmediate<mesh>(&mesh::InitData(L"./res/Meshes/skydome.obj", &resCreator),
		"sky_mesh", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("MeshGroup"), solidum); });
	
	Texture* grassTex = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/grass.png"),
		"grass_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
		
	Texture* woodTex = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/Wood.png"),
		"wood_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* metalTex = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/metal.png"),
		"metal_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* bricksTex = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/grey_bricks.png"),
		"bricks_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* bricksNormalMap = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/normals/bricks_normal.png"),
		"bricks_normal_map", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* skydomeCubeMap = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/cubemaps/sunsetcube1024.dds"),
		"cube_map", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* smokeTexture = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/smoke.png"),
		"smoke_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });
	
	Texture* fireTexture = (Texture*)resCreator.createResourceImmediate<Texture>(&Texture::InitData(L"./res/Textures/diffuse/fire.png"),
		"fire_tex", [=](IResource* res) { IResource::addResourceToGroup(res, std::string("TextureGroup"), solidum); });


	Material* brickMaterial = (Material*)resCreator.createResourceImmediate<Material>(&Material::InitData(), "brickMaterial", 
		[=](IResource* res) { IResource::addResourceToGroup(res, std::string("MaterialGroup"), solidum); });
		
	brickMaterial->createPass("basicPhongWSpecular", nullptr);
	
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularIntensity(5.5f);
	brickMaterial->getPass("basicPhongWSpecular")->setSpecularPower(20.0f);

	brickMaterial->getPass("basicPhongWSpecular")->setNormalTexture(bricksNormalMap);
	
	Material* woodMaterial = (Material*)resCreator.createResourceImmediate<Material>(&Material::InitData(), "woodMaterial",
		[=](IResource* res) { IResource::addResourceToGroup(res, std::string("MaterialGroup"), solidum); });

	woodMaterial->createPass("basicPhongWSpecular", nullptr);

	woodMaterial->getPass("basicPhongWSpecular")->setSpecularColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	woodMaterial->getPass("basicPhongWSpecular")->setSpecularIntensity(0.002f);
	woodMaterial->getPass("basicPhongWSpecular")->setSpecularPower(0.002f);

	KEY_FUNCTION_MAP* moveKeyConfig1 = new KEY_FUNCTION_MAP;
	KEY_FUNCTION_MAP* moveKeyConfig2 = new KEY_FUNCTION_MAP;

	moveKeyConfig1->insert({ KEY_MAP::UP, MOVE_FUNCTION::MOVE_UP});
	moveKeyConfig1->insert({ KEY_MAP::DOWN, MOVE_FUNCTION::MOVE_DOWN });
	moveKeyConfig1->insert({ KEY_MAP::LEFT, MOVE_FUNCTION::MOVE_LEFT });
	moveKeyConfig1->insert({ KEY_MAP::RIGHT, MOVE_FUNCTION::MOVE_RIGHT });
	moveKeyConfig1->insert({ KEY_MAP::U, MOVE_FUNCTION::MOVE_FORWARD });
	moveKeyConfig1->insert({ KEY_MAP::Y, MOVE_FUNCTION::MOVE_BACKWARD });

	moveKeyConfig2->insert({ KEY_MAP::I, MOVE_FUNCTION::MOVE_UP });
	moveKeyConfig2->insert({ KEY_MAP::K, MOVE_FUNCTION::MOVE_DOWN });
	moveKeyConfig2->insert({ KEY_MAP::J, MOVE_FUNCTION::MOVE_LEFT });
	moveKeyConfig2->insert({ KEY_MAP::L, MOVE_FUNCTION::MOVE_RIGHT });

	//** RESOURCE LOADING DONE **//

	sunLight->setColor(Vector4f(0.5f, 0.5f, 0.5f, 0.5f));
	sunLight->setDirection(Vector3f(-0.707f, -0.707f, 0));
	sunLight->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	sunLight->setIntensity(0.9f);

	fireLight->setColor(Vector4f(3.5f, 1.5f, 0.5f, 0.5f));
	fireLight->setDirection(Vector3f(0.0f, 0.0f, 0.0f));
	fireLight->setPosition(Vector3f(0, 0, 0));
	fireLight->setIntensity(7.0f);

	fireLight->setAttenuationLinear(0);
	fireLight->setAttenuationExponent(1);
	fireLight->setAttenuationConstant(0);

	fireLight->setRange(60.5f);

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
	pointLight2->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
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

	globalWorldLighting->addComponent<SunMoonLightingComponent>(new SunMoonLightingComponent(sunLight, moonLight, 0.1f, globalWorldLighting));

	Entity* sun = new Entity();

	sun->addComponent<LightComponent>(new LightComponent(sunLight, 0, sun, resCreator));

	Entity* pointLight1Entity = new Entity();

	pointLight1Entity->addComponent<MoveComponent>(new MoveComponent(Vector3f(4.0f, 0.01f, -1.8f), 0.5, false, moveKeyConfig2, pointLight1Entity));
	pointLight1Entity->addComponent<LightComponent>(new LightComponent(pointLight1, 0, pointLight1Entity, resCreator));

	Entity* pointLight2Entity = new Entity();

	pointLight2Entity->addComponent<MoveComponent>(new MoveComponent(Vector3f(0.2f, 0.01f, -5.0f), 0.5, false, moveKeyConfig1, pointLight2Entity));
	pointLight2Entity->addComponent<LightComponent>(new LightComponent(pointLight2, 0, pointLight2Entity, resCreator));

	Entity* pointLight3Entity = new Entity();

	pointLight3Entity->addComponent<MeshComponent>(new MeshComponent(cubeMesh, woodTex, woodMaterial, 0, pointLight3Entity));
	pointLight3Entity->addComponent<MoveComponent>(new MoveComponent(Vector3f(-0.2f, 0.01f, 8.0f), 0.5, false, moveKeyConfig1, pointLight3Entity));
	pointLight3Entity->addComponent<LightComponent>(new LightComponent(pointLight3, 0, pointLight3Entity, resCreator));

	Entity* fireLightEntity = new Entity();

	fireLightEntity->addComponent<MoveComponent>(new MoveComponent(Vector3f(0.0f, 3.0f, 0.0f), 0.5, false, moveKeyConfig1, fireLightEntity));
	fireLightEntity->addComponent<LightComponent>(new LightComponent(fireLight, 0, fireLightEntity, resCreator));

	Entity* hammer = new Entity();

	hammer->addComponent<MeshComponent>(new MeshComponent(cubeMesh, metalTex, brickMaterial, 0, hammer));

	Entity* cube = new Entity();

	cube->addComponent<MoveComponent>(new MoveComponent(Vector3f(0, -1.0f, 0), 0.5, false, moveKeyConfig1, cube));
	cube->addComponent<MeshComponent>(new MeshComponent(cubeMesh, woodTex, woodMaterial, 0, cube));

	Entity* plane = new Entity();

	plane->addComponent<MoveComponent>(new MoveComponent(Vector3f(0, -3.5, 0), 0.5, false, moveKeyConfig1, plane));
	plane->addComponent<MeshComponent>(new MeshComponent(planeMesh, bricksTex, woodMaterial, 0, plane));

	Entity* camera = new Entity();

	camera->addComponent<CameraComponent>(new CameraComponent(0.1f, 1000.0f, camera));

	Entity* sky = new Entity();

	sky->addComponent<SkydomeWeatherComponent>(new SkydomeWeatherComponent(skydomeCubeMap, skydomeMesh,
		(CameraComponent*)camera->getComponent<CameraComponent>(0),
		Vector4f(0.1f, 0.1f, 0.1f, 1.0f), Vector4f(0.1f, 0.1f, 0.1f, 1.0f), 0, sky));

	Entity* particleEmitter1Entity = new Entity();

	particleEmitter1Entity->addComponent<MoveComponent>(new MoveComponent(Vector3f(0, 6.0f, 0), 0.5, true, moveKeyConfig1, particleEmitter1Entity));
	
	particleEmitter1Entity->addComponent<ParticleEmitterComponent>(new ParticleEmitterComponent(110, 4.5, -0.5, 3, 200, 8, fireTexture, BLEND_STATE::ADDITIVE_BLENDING,
		(CameraComponent*)camera->getComponent<CameraComponent>(0), 
		particleEmitter1Entity, resCreator));

	Entity* particleEmitter2Entity = new Entity();

	particleEmitter2Entity->addComponent<MoveComponent>(new MoveComponent(Vector3f(-5.0f, 2.0f, 0), 0.5, false, moveKeyConfig1, particleEmitter2Entity));

	particleEmitter2Entity->addComponent<ParticleEmitterComponent>(new ParticleEmitterComponent(110, 4.5, -0.5, 3, 200, 8, smokeTexture, BLEND_STATE::ALPHA_BLENDING,
		(CameraComponent*)camera->getComponent<CameraComponent>(0),
		particleEmitter2Entity, resCreator));

	particleEmitter1Entity->addChild(cube);
	particleEmitter1Entity->addChild(fireLightEntity);

	world->addPrimaryCamera(camera, 0000);
	
	world->addEntity(particleEmitter2Entity, 8593);
	world->addEntity(particleEmitter1Entity, 5964);
	world->addEntity(sun, 3333);
	world->addEntity(pointLight2Entity, 0001);
	world->addEntity(pointLight3Entity, 0010);
	world->addEntity(globalWorldLighting, 1111);
	world->addEntity(hammer, 0011);
	world->addEntity(plane, 0100);
	world->addEntity(sky, 0101);

	solidum->start();

	myWindow->destroyWindow();
}

