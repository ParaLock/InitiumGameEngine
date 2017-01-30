#pragma once
class Vector4f {
private:
	float _x;
	float _y;
	float _z;
	float _w;
public:

	Vector4f(float x, float y, float z, float w) {
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	Vector4f() {

	}

	static inline Vector4f add(Vector4f vec1, Vector4f vec2) {

		Vector4f finalVec;

		finalVec._x = vec1._x + vec2._x;
		finalVec._y = vec1._y + vec2._y;
		finalVec._z = vec1._z + vec2._z;
		finalVec._w = vec1._w + vec2._w;

		return finalVec;
	};

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };
	void setZ(float z) { _z = z; };
	void setW(float w) { _w = w; };

	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getW() { return _w; }
};