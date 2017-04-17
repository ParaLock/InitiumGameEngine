#include "../include/BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector3f center, float radius)
{
	_center = center;
	_radius = radius;
}

BoundingSphere::~BoundingSphere()
{
}
