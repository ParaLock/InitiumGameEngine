#pragma once

class Vector2f {
private:
	float _x;
	float _y;
public:

	Vector2f(float x, float y) {
		_x = x;
		_y = y;
	}

	Vector2f() {

	}

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };

	float getX() { return _x; }
	float getY() { return _y; }
};