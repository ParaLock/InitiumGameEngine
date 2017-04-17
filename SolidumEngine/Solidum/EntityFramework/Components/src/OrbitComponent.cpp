#include "../include/OrbitComponent.h"



OrbitComponent::OrbitComponent(Vector3f pointToOrbit, float radius, float speed, IEntity* entity)
{
	_pointToOrbit = pointToOrbit;
	_orbitRadius = radius;

	_orbitSpeed = speed;

	_orbitAngle = 0.0f;

	setType(COMPONENT_TYPE::ORBIT_COMPONENT);

	_parent = entity;
}


OrbitComponent::~OrbitComponent()
{
}

void OrbitComponent::update(float delta)
{
	_orbitAngle += 0.009f;

	Matrix4f matRot;
	Matrix4f matTrans;

	matRot = Matrix4f::get_rotationX(_orbitAngle);
	matTrans = Matrix4f::get_translation(Vector3f(_pointToOrbit[0], _pointToOrbit[1], _orbitRadius));

	Matrix4f finalMatrix =  matRot * matTrans;

	_parent->getTransform()->setMatrix(finalMatrix);
}
