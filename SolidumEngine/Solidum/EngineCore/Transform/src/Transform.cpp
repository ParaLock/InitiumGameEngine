#include "../include/Transform.h"



Transform::Transform()
{
}


Transform::~Transform()
{
}



void Transform::setRotation(float angleOfRot, std::string direction) {

	if (direction == "x") {
		D3DXMatrixRotationX(&objMatrix, angleOfRot);
	}
	if (direction == "y") {
		D3DXMatrixRotationY(&objMatrix, angleOfRot);
	}
	if (direction == "z") {
		D3DXMatrixRotationZ(&objMatrix, angleOfRot);
	}
}

void Transform::setPos(float x, float y, float z) {

	D3DXMatrixTranslation(&objMatrix, pos.x, pos.y, pos.z);
}