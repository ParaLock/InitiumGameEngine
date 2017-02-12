#pragma once


template<typename T>
class Vector4
{
private:
	T d[4];
public:
	Vector4(const Vector4<T>& vec) {
		d[0] = vec[0];
		d[1] = vec[1];
		d[2] = vec[2];
		d[3] = vec[3];
	}

	Vector4() {
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;
		d[3] = 0;
	}

	Vector4(const T& x, const T& y, const T& z, const T& w) {
		d[0] = x;
		d[1] = y;
		d[2] = z;
		d[3] = w;
	}

	~Vector4() {
	}

	inline Vector4<T> operator+(const Vector4<T>& r) const
	{
		Vector4<T> result;

		result[0] = d[0] + r[0];
		result[1] = d[1] + r[1];
		result[2] = d[2] + r[2];
		result[3] = d[3] + r[3];

		return result;
	}

	inline Vector4<T> operator-(const Vector4<T>& r) const
	{
		Vector4<T> result;

		result[0] = d[0] - r[0];
		result[1] = d[1] - r[1];
		result[2] = d[2] - r[2];
		result[3] = d[3] - r[3];

		return result;
	}

	inline Vector4<T> operator*(const T& r) const
	{
		Vector4<T> result;

		result[0] = d[0] * r[0];
		result[1] = d[1] * r[1];
		result[2] = d[2] * r[2];
		result[3] = d[3] * r[3];

		return result;
	}

	inline Vector4<T> operator/(const T& r) const
	{
		Vector4<T> result;

		result[0] = d[0] / r[0];
		result[1] = d[1] / r[1];
		result[2] = d[2] / r[2];
		result[3] = d[3] / r[3];

		return result;
	}

	inline Vector4<T>& operator+=(const Vector4<T>& r)
	{
		d[0] = d[0] + r[0];
		d[1] = d[1] + r[1];
		d[2] = d[2] + r[2];
		d[3] = d[3] + r[3];

		return *this;
	}

	inline Vector4<T>& operator-=(const Vector4<T>& r)
	{
		d[0] = d[0] - r[0];
		d[1] = d[1] - r[1];
		d[2] = d[2] - r[2];
		d[3] = d[3] - r[3];

		return *this;
	}

	inline Vector4<T>& operator*=(const T& r)
	{
		d[0] = d[0] * r[0];
		d[1] = d[1] * r[1];
		d[2] = d[2] * r[2];
		d[3] = d[3] * r[3];

		return *this;
	}

	inline Vector4<T>& operator/=(const T& r)
	{
		d[0] = d[0] / r[0];
		d[1] = d[1] / r[1];
		d[2] = d[2] / r[2];
		d[3] = d[3] / r[3];

		return *this;
	}

	inline void operator=(const T& r) {
		d[0] = r[0];
		d[1] = r[1];
		d[2] = r[2];
		d[3] = r[3];
	}

	T& operator [] (unsigned int i) { return d[i]; }
	T operator [] (unsigned int i) const { return d[i]; }

	inline bool operator==(const Vector4<T>& r) const
	{
		if (d[0] != r[0] && d[1] != r[1] && d[2] != r[2] && d[3] != r[3])
			return false;
		return true;
	}

	inline bool operator!=(const Vector4<T>& r) const { return !operator==(r); }


	const static T length(Vector4<T>& vec1) {
		return std::sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2] + vec1[3] * vec1[3])
	};

	inline static Vector4<T> lerp(const Vector4<T>& vec1, const Vector4<T>& vec2, T lerpFactor) { return (vec1 - vec2) * lerpFactor + vec2; }

	const static Vector4<T> dot_product(Vector4<T>& vec1, Vector4<T>& vec2) {
		return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2] + vec1[3] * vec2[3];
	};

	const static T Max(Vector4<T>& vec) {
		T maxVal = vec[0];

		for (int i = 0; i < 4; i++)
			if (vec[i] > maxVal)
				maxVal = vec[i];

		return maxVal;
	};

	const static Vector4<T> normalize(Vector4<T>& vec) {
		T veclength = length(vec);

		Vector4<T> result;

		result[0] = vec[0] / length;
		result[1] = vec[1] / length;
		result[2] = vec[2] / length;
		result[3] = vec[3] / length;

		return result;
	};

	inline void setX(const T& x) { d[0] = x; }
	inline void setY(const T& y) { d[1] = y; }
	inline void setZ(const T& z) { d[2] = z; }
	inline void setW(const T& w) { d[3] = w; }

	inline T getX() { return d[0]; }
	inline T getY() { return d[1]; }
	inline T getZ() { return d[2]; }
	inline T getW() { return d[3]; }

	inline void set(const T& x, const T& y, const T& z, const T& w) { d[0] = x; d[1] = y; d[2] = z; d[3] = w; }
};

typedef Vector4<float> Vector4f;