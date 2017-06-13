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

std::shared_ptr<RenderDataPacket> MeshComponent::createRenderData()
{
	RenderPassPacket_MeshData data;

	data._indiceBuffer = _mesh->getIndexBuff();
	data._vertexBuffer = _mesh->getVertexBuff();

	data._globalTransform = _parent->getTransform()->getGlobalTransform();

	data._modelTex = _tex;

	data._numIndices = _mesh->numIndices;

	data._materialData._shader = _mat->getPassList().front()->getShader();
	data._materialData._specularColor = _mat->getPassList().front()->getSpecularColor();
	data._materialData._specularIntensity = _mat->getPassList().front()->getSpecularIntensity();
	data._materialData._specularPower = _mat->getPassList().front()->getSpecularPower();
	data._materialData._textures = _mat->getPassList().front()->getTextures();

	std::shared_ptr<RenderDataPacket> _dataPtr = std::make_shared<RenderDataPacket>();

	_dataPtr->setType(RENDER_DATA_TYPE::RENDER_MESH_DATA);

	_dataPtr->addData<RenderPassPacket_MeshData>(data);

	return _dataPtr;
}
