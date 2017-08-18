#pragma once
#ifndef _VECTOR2_H
#define _VECTOR2_H

template<typename T>
class Vector2
{
private:
	T d[2];
public:
	Vector2(const Vector2<T>& vec) {
		d[0] = vec[0];
		d[1] = vec[1];
	}

	Vector2() {
		d[0] = 0;
		d[1] = 0;
	}

	Vector2(const T& x, const T& y) {
		d[0] = x;
		d[1] = y;
	}

	~Vector2() {
	}

	inline Vector2<T> operator+(const Vector2<T>& r) const
	{
		Vector2<T> result;

		result[0] = d[0] + r[0];
		result[1] = d[1] + r[1];

		return result;
	}

	inline Vector2<T> operator-(const Vector2<T>& r) const
	{
		Vector2<T> result;

		result[0] = d[0] - r[0];
		result[1] = d[1] - r[1];

		return result;
	}

	inline Vector2<T> operator*(const T& r) const
	{
		Vector2<T> result;

		result[0] = d[0] * r[0];
		result[1] = d[1] * r[1];

		return result;
	}

	inline Vector2<T> operator/(const T& r) const
	{
		Vector2<T> result;

		result[0] = d[0] / r[0];
		result[1] = d[1] / r[1];

		return result;
	}

	inline Vector2<T>& operator+=(const Vector2<T>& r)
	{
		d[0] = d[0] + r[0];
		d[1] = d[1] + r[1];

		return *this;
	}

	inline Vector2<T>& operator-=(const Vector2<T>& r)
	{
		d[0] = d[0] - r[0];
		d[1] = d[1] - r[1];

		return *this;
	}

	inline Vector2<T>& operator*=(const T& r)
	{
		d[0] = d[0] * r[0];
		d[1] = d[1] * r[1];

		return *this;
	}

	inline Vector2<T>& operator/=(const T& r)
	{
		d[0] = d[0] / r[0];
		d[1] = d[1] / r[1];

		return *this;
	}

	inline void operator=(const Vector2<T>& r) {
		d[0] = r[0];
		d[1] = r[1];
	}

	inline void operator=(const T& r) {
		d[0] = r;
		d[1] = r;
	}

	T& operator [] (unsigned int i) { return d[i]; }
	T operator [] (unsigned int i) const { return d[i]; }

	inline bool operator==(const Vector2<T>& r) const
	{
		if (d[0] != r[0] && d[1] != r[1])
			return false;
		return true;
	}

	inline bool operator!=(const Vector2<T>& r) const { return !operator==(r); }

	inline static Vector2<T> length(const Vector2<T>& vec1) {
		return std::sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2]);
	};

	inline static Vector2<T> dot_product(const Vector2<T>& vec1, const Vector2<T>& vec2) {
		return vec1[0] * vec2[0] + vec1[1] * vec2[1];
	};

	inline static Vector2<T> cross_product(const Vector2<T>& vec1, const Vector2<T>& vec2) {
		return vec1[0] * vec2[1] - vec1[0] * vec2[1];
	};

	inline static Vector2<T> Max(const Vector2<T>& vec) {
		T maxVal = vec[0];

		for (int i = 0; i < 2; i++)
			if (vec[i] > maxVal)
				maxVal = vec[i];

		out = maxVal;
	};

	inline static Vector2<T> normalize(Vector2<T>& vec) {
		T veclength = length(vec);

		Vector2<T> result;

		result[0] = vec[0] / length;
		result[1] = vec[1] / length;
	};

	inline void setX(T x) { d[0] = x; }
	inline void setY(T y) { d[1] = y; }

	inline T& getX() { return d[0]; }
	inline T& getY() { return d[1]; }

	inline void set(const T& x, const T& y) { d[0] = x; d[1] = y; }
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

#endif