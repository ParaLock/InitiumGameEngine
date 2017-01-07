#include "../include/Transform.h"



Transform::Transform()
{
	D3DXMatrixIdentity(&_transformMatrix);
}


Transform::~Transform()
{
}

void Transform::setRotation(float angleOfRot, std::string direction) {

	if (direction == "x") {
		D3DXMatrixRotationX(&_transformMatrix, angleOfRot);
	}
	if (direction == "y") {
		D3DXMatrixRotationY(&_transformMatrix, angleOfRot);
	}
	if (direction == "z") {
		D3DXMatrixRotationZ(&_transformMatrix, angleOfRot);
	}
}

void Transform::setPos(Vector3f pos)
{
	_pos = pos;

	D3DXMatrixTranslation(&_transformMatrix, pos.getX(), pos.getY(), pos.getZ());
}

