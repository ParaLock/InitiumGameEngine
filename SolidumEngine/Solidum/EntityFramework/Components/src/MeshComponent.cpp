#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat, Shader* shader)
{
	RenderEvent* renderEvt = new RenderEvent(EVENT_TYPE::RENDER_EVENT_QUEUE_OP);
	_op = new RenderOP();

	_op->setMesh(mesh);
	_op->setMaterial(mat);
	_op->setTexture(tex);
	_op->setShader(shader);

	renderEvt->setRenderOP(_op);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(renderEvt);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::update()
{
	if (_parent != nullptr)
		_op->setTransform(_parent->getTransform());
}

void MeshComponent::onEvent(IEvent * evt)
{
}
