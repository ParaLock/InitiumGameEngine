#include "../include/Transform.h"



Transform::Transform()
{
	D3DXMatrixIdentity(&_transformMatrix);

	_pos._x = 0;
	_pos._y = 0;
	_pos._z = 0;

	isLoaded = true;
}


Transform::~Transform()
{
	isLoaded = false;
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


	D3DXMatrixTranslation(&_transformMatrix, _pos.getX(), _pos.getY(), _pos.getZ());
}

