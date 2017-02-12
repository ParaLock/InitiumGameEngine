#include "../include/Transform.h"



Transform::Transform()
{
	_transformMatrix = Matrix4f::get_identity();

	_pos[0] = 0;
	_pos[1] = 0;
	_pos[2] = 0;

	isLoaded = true;
}


Transform::~Transform()
{
	isLoaded = false;
}

void Transform::setRotation(float angleOfRot, ROT_DIR direction) {

	switch (direction)
	{
	case ROT_DIR::ROT_DOWN:
		break;
	default:
		break;
	}
}

void Transform::setPos(Vector3f pos)
{
	_pos = pos;

	_transformMatrix = Matrix4f::get_translation(pos);

}

