#pragma once

class Vector3f {
private:
	float _x;
	float _y;
	float _z;
public:

	Vector3f(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3f() {

	}

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };
	void setZ(float z) { _z = z; };

	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
};