#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat, Shader* shader)
{
	_op.setMesh(mesh);
	_op.setMaterial(mat);
	_op.setTexture(tex);
	_op.setShader(shader);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::update()
{
	if (_parent != nullptr)
		_op.setTransform(_parent->getTransform());

	EVENT_PTR renderEvt = std::make_shared<RenderEvent>(EVENT_TYPE::RENDER_EVENT_QUEUE_OP);

	renderEvt.get()->getEvent<RenderEvent>()->setRenderOP(_op);

	EventFrameworkCore::getInstance()->
		getGlobalEventHub("ComponentEventHub")->publishEvent(renderEvt);
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
