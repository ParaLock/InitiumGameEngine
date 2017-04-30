#pragma once

template<typename T>
class Vector3
{
private:
	T d[3];
public:
	Vector3(const Vector3<T>& vec) {
		d[0] = vec[0];
		d[1] = vec[1];
		d[2] = vec[2];
	}

	Vector3() {
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;
	}

	Vector3(const T& x, const T& y, const T& z) {
		d[0] = x;
		d[1] = y;
		d[2] = z;
	}

	~Vector3() {
	}

	inline Vector3<T> operator+(const Vector3<T>& r) const
	{
		Vector3<T> result;

		result[0] = d[0] + r[0];
		result[1] = d[1] + r[1];
		result[2] = d[2] + r[2];

		return result;
	}

	inline Vector3<T> operator-(const Vector3<T>& r) const
	{
		Vector3<T> result;

		result[0] = d[0] - r[0];
		result[1] = d[1] - r[1];
		result[2] = d[2] - r[2];

		return result;
	}

	inline Vector3<T> operator-() const {
		return Vector3<T>(-d[0], -d[1], -d[2]);
	}

	inline Vector3<T> operator*(const T& r) const
	{
		Vector3<T> result;

		result[0] = d[0] * r;
		result[1] = d[1] * r;
		result[2] = d[2] * r;

		return result;
	}

	inline Vector3<T> operator/(const T& r) const
	{
		Vector3<T> result;

		result[0] = d[0] / r;
		result[1] = d[1] / r;
		result[2] = d[2] / r;

		return result;
	}

	inline Vector3<T>& operator+=(const Vector3<T>& r)
	{

		d[0] += r[0];
		d[1] += r[1];
		d[2] += r[2];

		return *this;
	}

	inline Vector3<T>& operator+=(const T& r)
	{
		d[0] += r;
		d[1] += r;
		d[2] += r;

		return *this;
	}

	inline Vector3<T>& operator-=(const Vector3<T>& r)
	{
		d[0] = d[0] - r[0];
		d[1] = d[1] - r[1];
		d[2] = d[2] - r[2];

		return *this;
	}

	inline Vector3<T>& operator*=(const T& r)
	{
		d[0] = d[0] * r;
		d[1] = d[1] * r;
		d[2] = d[2] * r;

		return *this;
	}

	inline Vector3<T>& operator/=(const T& r)
	{
		d[0] = d[0] / r;
		d[1] = d[1] / r;
		d[2] = d[2] / r;

		return *this;
	}

	inline void operator=(const T& r) {
		d[0] = r;
		d[1] = r;
		d[2] = r;
	}

	T& operator [] (unsigned int i) { return d[i]; }
	T operator [] (unsigned int i) const { return d[i]; }

	inline bool operator==(const Vector3<T>& r) const
	{
		if (d[0] != r[0] && d[1] != r[1] && d[2] != r[2])
			return false;
		return true;
	}

	inline bool operator!=(const Vector3<T>& r) const { return !operator==(r); }

	inline static T length(Vector3<T>& vec) {
		return std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	};

	inline static T dot_product(Vector3<T>& vec1, Vector3<T>& vec2) {
		return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
	};

	inline static Vector3<T> cross_product(Vector3<T>& vec1, Vector3<T>& vec2) {

		Vector3<T> result;

		T x = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		T y = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		T z = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		result[0] = x;
		result[1] = y;
		result[2] = z;

		return result;
	};

	inline static T Max(Vector3<T>& vec) {
		T maxVal = vec[0];

		for (int i = 0; i < 3; i++)
			if (vec[i] > maxVal)
				maxVal = d[i];

		return maxVal;
	};

	inline static Vector3<T> normalize(Vector3<T>& vec) {
		T vecLength = length(vec);

		Vector3<T> result;

		if (vecLength == 0) {
			result[0] = 0;
			result[1] = 0;
			result[2] = 0;
		}

		result[0] = vec[0] / vecLength;
		result[1] = vec[1] / vecLength;
		result[2] = vec[2] / vecLength;

		return result;
	};

	inline static T distance_between(const Vector3<T>& vec1, const Vector3<T>& vec2) {
		const Vector3<T> diff = vec1 - vec2;
		return Vector3<T>::length(diff);
	}

	inline static Vector3<T> rotate(T angle, const Vector3<T>& axis, const Vector3<T>& vec) {

		const T sin = sinf(-angle);
		const T cos = cosf(-angle);

		return this->cross_product(axis * sin) +
			(vec * cos) +
			axis * dot_product(vec, axis * (1 - cos));
	}



	inline void setX(T x) { d[0] = x; }
	inline void setY(T y) { d[1] = y; }
	inline void setZ(T z) { d[2] = z; }

	inline T& getX() { return d[0]; }
	inline T& getY() { return d[1]; }
	inline T& getZ() { return d[2]; }

	inline void set(const T& x, const T& y, const T& z) { d[0] = x; d[1] = y; d[2] = z; }
};

typedef Vector3<float> Vector3f;