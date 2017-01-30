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

	static inline Vector2f add(Vector2f vec1, Vector2f vec2) {

		Vector2f finalVec;

		finalVec._x = vec1._x + vec2._x;
		finalVec._y = vec1._y + vec2._y;

		return finalVec;
	};

	void setX(float x) { _x = x; };
	void setY(float y) { _y = y; };

	float getX() { return _x; }
	float getY() { return _y; }
};