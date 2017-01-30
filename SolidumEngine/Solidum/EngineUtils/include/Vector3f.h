#pragma once

class Vector3f {
private:

public:

	float _x;
	float _y;
	float _z;

	Vector3f(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3f() {

	}

	static inline Vector3f add(Vector3f vec1, Vector3f vec2) {

		Vector3f finalVec;

		finalVec._x = vec1._x + vec2._x;
		finalVec._y = vec1._y + vec2._y;
		finalVec._z = vec1._z + vec2._z;

		return finalVec;
	};

	bool equals (Vector3f& vec) const
	{
		return _x == vec._x && _y == vec._y && _z == vec._z;
	}

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };
	void setZ(float z) { _z = z; };

	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
};