#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat, std::string rendProcID)
{
	_mesh = mesh;
	_tex = tex;
	_mat = mat;

	EVENT_PTR regEvt = std::make_shared<RenderEvent>(EVENT_TYPE::RENDER_EVENT_REGISTER_STREAM);

	_graphicsStream = new RenderDataStream();

	regEvt->getEvent<RenderEvent>()->setData(_graphicsStream, rendProcID);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(regEvt);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::update()
{
	if (_parent != nullptr)
		_transform = _parent->getTransform();

	if(_transform != nullptr)
		_graphicsStream->insertData((IResource*)_parent->getTransform(), STREAM_DATA_TYPE::TRANSFORM);

	_graphicsStream->insertData((IResource*)_mat, STREAM_DATA_TYPE::MATERIAL);
	_graphicsStream->insertData((IResource*)_mesh, STREAM_DATA_TYPE::MESH);
	_graphicsStream->insertData((IResource*)_tex, STREAM_DATA_TYPE::TEXTURE);
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
