#pragma once
#include "Component.h"
#include "../../../GraphicsRendering/Mesh/include/mesh.h"
#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../GraphicsRendering/Material/include/Material.h"
#include "../../../GraphicsRendering/Textures/include/Texture.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataGroup.h"

struct RenderPassPacket_MaterialData {

	float _specularIntensity;
	float _specularPower;

	Shader* _shader;

	Vector4f _specularColor;

	IResource* _albedoTex = nullptr;
	IResource* _specularTex = nullptr;
	IResource* _normalTex = nullptr;
	IResource* _roughnessTex = nullptr;
	IResource* _emissiveTex = nullptr;
};

struct RenderPassPacket_MeshData {

	int _numIndices;

	Matrix4f _globalTransform;

	IResource* _indiceBuffer;
	IResource* _vertexBuffer;

	IResource* _modelTex;

	RenderPassPacket_MaterialData _materialData;
};

class MeshComponent : public Component
{
private:
	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	mesh* _mesh;
	Texture* _tex;
	Material* _mat;
public:
	MeshComponent(mesh* mesh, Texture* tex, Material* mat, int index, IEntity* entity);
	~MeshComponent();

	void setTexture(Texture* tex) { _tex = tex; }
	void setMaterial(Material* mat) { _mat = mat; }

	void update(float delta);
	void onEvent(EVENT_PTR evt);

	void AddRenderData(RenderDataGroup* collection);
};

