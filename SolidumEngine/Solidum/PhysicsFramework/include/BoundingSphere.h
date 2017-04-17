#pragma once
#include "../../sysInclude.h"

class BoundingSphere
{
private:
	Vector3f _center;
	float    _radius;
public:
	BoundingSphere(Vector3f center, float radius);
	~BoundingSphere();

	Vector3f getCenter() { return _center; }
	float getRadius() { return _radius; }
};

