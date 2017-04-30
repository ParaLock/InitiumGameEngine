#include "../include/Transform.h"



Transform::Transform()
{
	_localTransformMatrix = Matrix4f::get_identity();
	_globalTransformMatrix = Matrix4f::get_identity();

	_vecPos = Vector3f(0,0,0);
	_vecScale = Vector3f(1, 1, 1);

	isLoaded = true;
}


Transform::~Transform()
{
	isLoaded = false;
}

void Transform::buildTransform()
{
	Matrix4f matScale, matRotation, matTranslation;

	matRotation = Matrix4f::get_identity();

	matTranslation = Matrix4f::get_translation(_vecPos);
	matScale = Matrix4f::get_scale(_vecScale);

	setGlobalTransform(matTranslation * matRotation);
}

void Transform::setParent(Transform * transform)
{
	if (_parent == transform)
		return;

	if (_parent)
		_globalTransformMatrix = getGlobalTransform();
	
	_parent = transform;

	if (!transform)
		return;


	_localTransformMatrix = Matrix4f::invert(_parent->getGlobalTransform()) * _globalTransformMatrix;
}


void Transform::setPosition(Vector3f pos)
{
	_vecPos = pos;

	buildTransform();
}

void Transform::setScale(Vector3f scale)
{
}

void Transform::setRotation(Vector3f axis, float angle)
{
}

void Transform::setGlobalTransform(Matrix4f global)
{
	if (_parent) {

		_localTransformMatrix = Matrix4f::invert(_parent->getGlobalTransform()) * global;

		return;
	}

	_globalTransformMatrix = global;
}

void Transform::setGlobalOrigin(Vector3f vecOrigin)
{
	if (_parent) {
		_localTransformMatrix = Matrix4f::get_translation(Matrix4f::invert(_parent->getGlobalTransform()) * vecOrigin);
		return;
	}

	_globalTransformMatrix = Matrix4f::get_translation(vecOrigin);
}

Vector3f Transform::getGlobalOrigin()
{
	return Matrix4f::getPos(getGlobalTransform());
}

Matrix4f Transform::getGlobalTransform()
{
	if (_parent) {

		Matrix4f parentGlobal = _parent->getGlobalTransform();

		Matrix4f result = parentGlobal * _localTransformMatrix;

		return result;
	}

	return _globalTransformMatrix;
}

