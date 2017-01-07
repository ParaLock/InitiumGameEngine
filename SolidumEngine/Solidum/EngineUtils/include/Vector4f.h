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

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };
	void setZ(float z) { _z = z; };
	void setW(float w) { _w = w; };

	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getW() { return _w; }
};