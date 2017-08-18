#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

template<typename T>
class Matrix3x3 {
private:
	T m[3][3];
public:

	Matrix3x3<T>() {

	}

	Matrix3x3<T>(const Matrix3x3<T>& r)
	{
		for (unsigned int i = 0; i < 3; i++)
			for (unsigned int j = 0; j < 3; j++)
				(*this)[i][j] = r[i][j];
	}

	inline Matrix3x3<T> operator*(const Matrix3x3<T>& r) 
	{
		Matrix3x3<T> ret;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				ret.m[i][j] = T(0);
				for (unsigned int k = 0; k < 3; k++)
					ret.m[i][j] += m[k][j] * r.m[i][k];
			}
		}
		return ret;
	}

	inline static Matrix3x3<T> get_scale(const Vector2<T>& r)
	{
		Matrix3x3<T> result;

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (i == j && i != 3 - 1)
					result[i][j] = r[i];
				else
					result[i][j] = T(0);
			}
		}

		result[3 - 1][3 - 1] = T(1);

		return result;
	}

	inline static Matrix3x3<T> init_translation(const Vector2<T>& r)
	{
		Matrix3x3<T> result;

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (i == 3 - 1 && j != 3 - 1)
					result[i][j] = r[j];
				else if (i == j)
					result[i][j] = T(1);
				else
					result[i][j] = T(0);
			}
		}

		result[3 - 1][3 - 1] = T(1);

		return result;
	}

	inline static Matrix3x3<T> transpose(const Matrix3x3<T>& mat)
	{
		Matrix3x3<T> t;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				t[i][j] = mat[j][i];
			}
		}
		return t;
	}

	inline static Vector3<T> transform(const Vector3<T>& r, const Matrix3x3<T>& mat)
	{
		Vector3<T> ret;

		for (unsigned int i = 0; i < 3; i++)
		{
			ret[i] = 0;
			for (unsigned int j = 0; j < 3; j++)
				ret[i] += mat[j][i] * r[j];
		}

		return ret;
	}

	inline void set(unsigned int x, unsigned int y, T val) { m[x][y] = val; }

	inline const T* operator[](int index) const { return m[index]; }
	inline T* operator[](int index) { return m[index]; }
};

typedef Matrix3x3<float> Matrix3f;