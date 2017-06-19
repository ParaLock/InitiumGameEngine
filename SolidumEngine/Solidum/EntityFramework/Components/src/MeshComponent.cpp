#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat, int index, IEntity* entity)
{
	_index = index;

	_mesh = mesh;
	_tex = tex;
	_mat = mat;

	_parent = entity;

	setType(COMPONENT_TYPE::MESH_COMPONENT);

	//Static meshes are always index + 1
	_parent->getRenderObject()->addMeshComponent(this, _index + 1);
	_parent->getRenderObject()->setMeshTexture(_tex, _index + 1);
	_parent->getRenderObject()->setMeshMaterial(_mat, _index + 1);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::update(float delta)
{
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}

void MeshComponent::AddRenderData(RenderDataGroup * collection)
{
	RenderPassPacket_MeshData data;

	RenderDataAttributes attributes;

	data._indiceBuffer = _mesh->getIndexBuff();
	data._vertexBuffer = _mesh->getVertexBuff();

	data._globalTransform = _parent->getTransform()->getGlobalTransform();

	data._modelTex = _tex;

	data._numIndices = _mesh->numIndices;

	data._materialData._shader = _mat->getPassList().front()->getShader();
	data._materialData._specularColor = _mat->getPassList().front()->getSpecularColor();
	data._materialData._specularIntensity = _mat->getPassList().front()->getSpecularIntensity();
	data._materialData._specularPower = _mat->getPassList().front()->getSpecularPower();

	data._materialData._albedoTex = _mat->getPassList().front()->getPBRAlbedoTexture();
	data._materialData._emissiveTex = _mat->getPassList().front()->getPBREmessiveTexture();
	data._materialData._normalTex = _mat->getPassList().front()->getNormalTexture();
	data._materialData._roughnessTex = _mat->getPassList().front()->getPBRRoughnessTexture();
	data._materialData._specularTex = _mat->getPassList().front()->getSpecularTexture();

	collection->addRenderData<RenderPassPacket_MeshData>(&data, RENDER_DATA_TYPE::RENDER_MESH_DATA, &attributes);
}
