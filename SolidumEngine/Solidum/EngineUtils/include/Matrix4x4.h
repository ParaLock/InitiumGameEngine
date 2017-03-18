#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

template<typename T>
class Matrix4x4 {
private:
	T m[4][4];
public:

	Matrix4x4<T>() {

	}

	Matrix4x4<T>(const Matrix4x4<T>& r)
	{	
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				(*this)[i][j] = r[i][j];
	}

	inline static Matrix4x4<T> get_identity()
	{
		Matrix4x4<T> result;

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j)
					result[i][j] = T(1);
				else
					result[i][j] = T(0);
			}
		}

		return result;
	}

	inline static Matrix4x4<T> get_scale(const Vector3<T>& r)
	{
		Matrix4x4<T> result;

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j && i != 4 - 1)
					result[i][j] = r[i];
				else
					result[i][j] = T(0);
			}
		}

		result[4 - 1][4 - 1] = T(1);

		return result;
	}

	inline Matrix4x4<T> get_rotation_euler(T rotateX, T rotateY, T rotateZ)
	{
		Matrix4x4<T> rx, ry, rz;

		const T x = rotateX;
		const T y = rotateY;
		const T z = rotateZ;

		rx[0][0] = T(1);   rx[1][0] = T(0);  rx[2][0] = T(0); rx[3][0] = T(0);
		rx[0][1] = T(0);   rx[1][1] = cos(x);  rx[2][1] = -sin(x); rx[3][1] = T(0);
		rx[0][2] = T(0);   rx[1][2] = sin(x);  rx[2][2] = cos(x); rx[3][2] = T(0);
		rx[0][3] = T(0);   rx[1][3] = T(0);  rx[2][3] = T(0); rx[3][3] = T(1);

		ry[0][0] = cos(y); ry[1][0] = T(0);    ry[2][0] = -sin(y); ry[3][0] = T(0);
		ry[0][1] = T(0); ry[1][1] = T(1);    ry[2][1] = T(0); ry[3][1] = T(0);
		ry[0][2] = sin(y); ry[1][2] = T(0);    ry[2][2] = cos(y); ry[3][2] = T(0);
		ry[0][3] = T(0); ry[1][3] = T(0);    ry[2][3] = T(0); ry[3][3] = T(1);

		rz[0][0] = cos(z); rz[1][0] = -sin(z); rz[2][0] = T(0);    rz[3][0] = T(0);
		rz[0][1] = sin(z); rz[1][1] = cos(z); rz[2][1] = T(0);    rz[3][1] = T(0);
		rz[0][2] = T(0); rz[1][2] = T(0); rz[2][2] = T(1);    rz[3][2] = T(0);
		rz[0][3] = T(0); rz[1][3] = T(0); rz[2][3] = T(0);    rz[3][3] = T(1);

		Matrix4x4<T> result = rz * ry * rx;

		return result;
	}

	inline static Matrix4x4<T> get_rotationX(float angle) {
		Matrix4x4<T> _result = Matrix4x4<T>::get_identity();

		_result[1][1] = cos(angle);
		_result[2][2] = cos(angle);
		_result[1][2] = sin(angle);
		_result[2][1] = -sin(angle);

		return _result;
	}

	inline static Matrix4x4<T> get_translation(const Vector3<T>& r)
	{
		Matrix4x4<T> result;

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == 4 - 1 && j != 4 - 1)
					result[i][j] = r[j];
				else if (i == j)
					result[i][j] = T(1);
				else
					result[i][j] = T(0);
			}
		}

		result[4 - 1][4 - 1] = T(1);

		return result;
	}

	inline static Matrix4x4<T> transpose(const Matrix4x4<T>& mat)
	{
		Matrix4x4<T> t;
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				t[i][j] = mat[j][i];
			}
		}
		return t;
	}

	inline Matrix4x4<T> operator*(const Matrix4x4<T>& r) const
	{
		Matrix4x4<T> ret;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				ret.m[i][j] = T(0);
				for (unsigned int k = 0; k < 4; k++)
					ret.m[i][j] += m[k][j] * r.m[i][k];
			}
		}
		return ret;
	}

	inline static Vector3<T> transform(const Vector3<T>& r, const Matrix4x4<T>& mat)
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

	inline static Matrix4x4<T> rotation_from_vectors(const Vector3<T>& n, const Vector3<T>& v, const Vector3<T>& u)
	{
		Matrix4x4<T> mat;

		mat[0][0] = u[0];   mat[1][0] = u[1];   mat[2][0] = u[2];   mat[3][0] = T(0);
		mat[0][1] = v[0];   mat[1][1] = v[1];   mat[2][1] = v[2];   mat[3][1] = T(0);
		mat[0][2] = n[0];   mat[1][2] = n[1];   mat[2][2] = n[2];   mat[3][2] = T(0);
		mat[0][3] = T(0);   mat[1][3] = T(0);   mat[2][3] = T(0);   mat[3][3] = T(1);

		return mat;
	}

	inline static Matrix4x4<T> rotation_from_direction(const Vector3<T>& forward, const Vector3<T>& up, const Matrix4x4<T>& mat)
	{
		Vector3<T> n = Vector3<T>::normalize(forward);
		Vector3<T> u = Vector3<T>(Vector3<T>::cross_product(Vector3<T>::normalize(up), n));
		Vector3<T> v = Vector3<T>::cross_product(n, u);

		return Vector3<T>::init_rotation_from_vectors(n, v, u, mat);
	}


	inline static Matrix4x4<T> get_perspective(T fov, T aspectRatio, T zNear, T zFar)
	{
		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		const T zRange = zNear - zFar;
		const T tanHalfFOV = tanf(fov / T(2));

		result[0][0] = T(1) / (tanHalfFOV * aspectRatio); result[1][0] = T(0);   result[2][0] = T(0);            result[3][0] = T(0);
		result[0][1] = T(0);                   result[1][1] = T(1) / tanHalfFOV; result[2][1] = T(0);            result[3][1] = T(0);
		result[0][2] = T(0);                   result[1][2] = T(0);            result[2][2] = (-zNear - zFar) / zRange; result[3][2] = T(2)*zFar*zNear / zRange;
		result[0][3] = T(0);                   result[1][3] = T(0);            result[2][3] = T(1);            result[3][3] = T(0);

		return result;
	}

	inline static Matrix4x4<T> get_orthographic(T left, T right, T bottom, T top, T Near, T Far)
	{
		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		const T width = (right - left);
		const T height = (top - bottom);
		const T depth = (Far - Near);

		result[0][0] = T(2) / width; result[1][0] = T(0);        result[2][0] = T(0);        result[3][0] = -(right + left) / width;
		result[0][1] = T(0);       result[1][1] = T(2) / height; result[2][1] = T(0);        result[3][1] = -(top + bottom) / height;
		result[0][2] = T(0);       result[1][2] = T(0);        result[2][2] = T(-2) / depth; result[3][2] = -(Far + Near) / depth;
		result[0][3] = T(0);       result[1][3] = T(0);        result[2][3] = T(0);        result[3][3] = T(1);

		return result;
	}

	inline static Matrix4x4<T> get_lookAt(Vector3<T> eye, Vector3<T> at, Vector3<T> up)
	{
		Matrix4x4<T> result;

		Vector3<T> zaxis = Vector3<T>::normalize(at - eye);
		Vector3<T> xaxis = Vector3<T>::normalize(Vector3<T>::cross_product(up, zaxis));
		Vector3<T> yaxis = Vector3<T>::cross_product(zaxis, xaxis);


		result[0][0] = xaxis[0];			result[0][1] = yaxis[0];			result[0][2] = zaxis[0];			result[0][3] = 0;
		result[1][0] = xaxis[1];			result[1][1] = yaxis[1];			result[1][2] = zaxis[1];			result[1][3] = 0;
		result[2][0] = xaxis[2];			result[2][1] = yaxis[2];			result[2][2] = zaxis[2];			result[2][3] = 0;
		result[3][0] = -Vector3<T>::dot_product(eye, xaxis);	result[3][1] = -Vector3<T>::dot_product(eye, yaxis);	result[3][2] = -Vector3<T>::dot_product(eye, zaxis);	result[3][3] = 1;

		return result;
	}

	inline static Matrix4x4<T> get_rot_of_YawPitchRoll(T roll, T pitch, T yaw) {
		Matrix4x4<T> result;

		result[0][0] = (cos(roll) * cos(yaw)) + (sin(roll) * sin(pitch) * sin(yaw));
		result[0][1] = (sin(roll) * cos(pitch));
		result[0][2] = (cos(roll) * -sin(yaw)) + (sin(roll) * sin(pitch) * cos(yaw));
		result[1][0] = (-sin(roll) * cos(yaw)) + (cos(roll) * sin(pitch) * sin(yaw));
		result[1][1] = (cos(roll) * cos(pitch));
		result[1][2] = (sin(roll) * sin(yaw)) + (cos(roll) * sin(pitch) * cos(yaw));
		result[2][0] = (cos(pitch) * sin(yaw));
		result[2][1] = -sin(pitch);
		result[2][2] = (cos(pitch) * cos(yaw));
		result[3][3] = 1;

		return result;
	}

	inline void set(unsigned int x, unsigned int y, T val) { m[x][y] = val; }
	inline T get(unsigned int x, unsigned int y) { return m[x][y]; }

	inline const T* operator[](int index) const { return m[index]; }
	inline T* operator[](int index) { return m[index]; }
};

typedef Matrix4x4<float> Matrix4f;