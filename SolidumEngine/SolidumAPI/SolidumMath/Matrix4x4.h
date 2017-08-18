#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

template<typename T>
class Matrix4x4 {
private:
public:
	T m[4][4];

	Matrix4x4<T>() {
		
	}

	Matrix4x4<T>(const Matrix4x4<T>& r)
	{	
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				(*this)[i][j] = r[i][j];
	}

	inline Matrix4x4<T> operator*(const T& f) const
	{
		Matrix4x4<T> r;

		r.m[0][0] = m[0][0] * f;
		r.m[0][1] = m[0][1] * f;
		r.m[0][2] = m[0][2] * f;
		r.m[0][3] = m[0][3] * f;

		r.m[1][0] = m[1][0] * f;
		r.m[1][1] = m[1][1] * f;
		r.m[1][2] = m[1][2] * f;
		r.m[1][3] = m[1][3] * f;

		r.m[2][0] = m[2][0] * f;
		r.m[2][1] = m[2][1] * f;
		r.m[2][2] = m[2][2] * f;
		r.m[2][3] = m[2][3] * f;

		r.m[3][0] = m[3][0] * f;
		r.m[3][1] = m[3][1] * f;
		r.m[3][2] = m[3][2] * f;
		r.m[3][3] = m[3][3] * f;

		return r;
	}

	//inline Matrix4x4<T> operator*(const Matrix4x4<T>& t) const
	//{
	//	Matrix4x4<T> r;

	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int j = 0; j < 4; j++)
	//			r[i][j] = m[0][j] * t[i][0] + m[1][j] * t[i][1] + m[2][j] * t[i][2] + m[3][j] * t[i][3];
	//	}

	//	return r;
	//}

	inline Matrix4x4<T> operator-(const Vector3<T>& t) const {

		m[3][0] += v.x;
		m[3][1] += v.y;
		m[3][2] += v.z;

		return *this;
	}

	inline Matrix4x4<T> operator-(const Matrix4x4<T>& t) const {

		Matrix4x4<T> r;

		r.m[0][0] = m[0][0] - t.m[0][0];
		r.m[0][1] = m[0][1] - t.m[0][1];
		r.m[0][2] = m[0][2] - t.m[0][2];
		r.m[0][3] = m[0][3] - t.m[0][3];

		r.m[1][0] = m[1][0] - t.m[1][0];
		r.m[1][1] = m[1][1] - t.m[1][1];
		r.m[1][2] = m[1][2] - t.m[1][2];
		r.m[1][3] = m[1][3] - t.m[1][3];

		r.m[2][0] = m[2][0] - t.m[2][0];
		r.m[2][1] = m[2][1] - t.m[2][1];
		r.m[2][2] = m[2][2] - t.m[2][2];
		r.m[2][3] = m[2][3] - t.m[2][3];

		r.m[3][0] = m[3][0] - t.m[3][0];
		r.m[3][1] = m[3][1] - t.m[3][1];
		r.m[3][2] = m[3][2] - t.m[3][2];
		r.m[3][3] = m[3][3] - t.m[3][3];

		return r;
	}

	inline Vector3<T> operator*(const Vector3<T>& v) const
	{

		Vector3<T> vecResult;

		vecResult[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0];
		vecResult[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1];
		vecResult[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2];

		return vecResult;
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
				if (i == j && i != 3)
					result[i][j] = r[i];
				else
					result[i][j] = T(0);
			}
		}

		result[3][3] = T(1);

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

	inline static Matrix4x4<T> get_rotationY(float angle) {
		Matrix4x4<T> _result = Matrix4x4<T>::get_identity();

		_result[1][1] = cos(angle);
		_result[2][2] = cos(angle);
		_result[1][2] = -sin(angle);
		_result[2][1] = sin(angle);

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

	inline static Vector3<T> getPos(Matrix4x4<T> mat) {
		Vector3<T> pos;

		pos[0] = mat[3][0];
		pos[1] = mat[3][1];
		pos[2] = mat[3][2];

		return pos;
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

	inline static Matrix4x4<T> rotate(Vector3<T> forward, Vector3<T> up, Matrix4x4<T> mat)
	{
		Vector3<T> f = Vector3<T>::normalize(forward);

		Vector3<T> r = Vector3<T>::normalize(up);

		r = Vector3<T>::cross_product(r, f);

		Vector3f u = Vector3<T>::cross_product(f, r);

		return rotate(f, u, r, mat);
	}

	inline static Matrix4x4<T> rotate(Vector3<T> forward, Vector3<T> up, Vector3<T> right, Matrix4x4<T> mat)
	{
		Vector3<T> f = forward;
		Vector3<T> r = right;
		Vector3<T> u = up;

		mat[0][0] = r[0];	mat[0][1] = r[1];	mat[0][2] = r[2];
		mat[1][0] = u[0];	mat[1][1] = u[1];	mat[1][2] = u[2];	
		mat[2][0] = f[0];	mat[2][1] = f[1];	mat[2][2] = f[2];

		return mat;
	}

	inline static Matrix4x4<T> get_perspectiveLH(T fov, T aspectRatio, T zNear, T zFar)
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

	inline static Matrix4x4<T> get_perspectiveRH(T fov, T aspectRatio, T zNear, T zFar)
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

	inline static Matrix4x4<T> get_orthographicLH(T left, T right, T bottom, T top, T Near, T Far)
	{
		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		const T width = (right - left);
		const T height = (top - bottom);
		const T depth = (Far - Near);

		result[0][0] = T(2) / width; result[1][0] = T(0);        result[2][0] = T(0);          result[3][0] = 0;
		result[0][1] = T(0);       result[1][1] = T(2) / height; result[2][1] = T(0);          result[3][1] = 0;
		result[0][2] = T(0);       result[1][2] = T(0);          result[2][2] = T(1) /(Far-Near);  result[3][2] = 0;
		result[0][3] = T(0);       result[1][3] = T(0);          result[2][3] = Near/(Near-Far);          result[3][3] = T(1);

		return result;
	}

	inline static Matrix4x4<T> get_orthographicRH(T left, T right, T bottom, T top, T Near, T Far)
	{
		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		const T width = (right - left);
		const T height = (top - bottom);
		const T depth = (Far - Near);

		result[0][0] = T(2) / width; result[1][0] = T(0);        result[2][0] = T(0);				result[3][0] = 0;
		result[0][1] = T(0);       result[1][1] = T(2) / height; result[2][1] = T(0);				result[3][1] = 0;
		result[0][2] = T(0);       result[1][2] = T(0);        result[2][2] = T(1) / (Near-Far);	result[3][2] = 0;
		result[0][3] = T(0);       result[1][3] = T(0);        result[2][3] = Near/(Near-Far);		result[3][3] = T(1);

		return result;
	}

	inline static Matrix4x4<T> get_orthographicOffCenterRH(T left, T right, T bottom, T top, T Near, T Far) {

		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		const T width = (right - left);
		const T height = (top - bottom);

		const T depth = (Far - Near);

		result[0][0] = T(2 / (right - left));					result[1][0] = T(0);									result[2][0] = T(0);				 result[3][0] = T(0);
		result[0][1] = T(0);								result[1][1] = T(2 / (top - bottom));						result[2][1] = T(0);				 result[3][1] = T(0);
		result[0][2] = T(0);								result[1][2] = T(0);									result[2][2] = T(1 / (Near - Far));		 result[3][2] = T(0);
		result[0][3] = T((left + right) / (left - right));        result[1][3] = T((top + bottom) / (bottom - top));			result[2][3] = T(Near / (Near - Far));	 result[3][3] = T(1);

		return result;
	}

	inline static Matrix4x4<T> get_orthographicOffCenterLH(T left, T right, T bottom, T top, T Near, T Far) {
		
		Matrix4x4<T> result;

		result = Matrix4x4<T>::get_identity();

		result[0][0] = T(2 / (right - left));					  result[1][0] = T(0);									result[2][0] = T(0);				 result[3][0] = T(0);
		result[0][1] = T(0);									  result[1][1] = T(2/(top-bottom));						result[2][1] = T(0);				 result[3][1] = T(0);
		result[0][2] = T(0);									  result[1][2] = T(0);									result[2][2] = T(1/(Far-Near));		 result[3][2] = T(0);
		result[0][3] = T((left + right) / (left - right));        result[1][3] = T((top+bottom)/(bottom-top));			result[2][3] = T(Near /(Near-Far));	 result[3][3] = T(1);

		return result;
	}



	inline static Matrix4x4<T> get_lookAtRH(Vector3<T> eye, Vector3<T> at, Vector3<T> up)
	{
		Matrix4x4<T> result;

		Vector3<T> zaxis = Vector3<T>::normalize(eye - at);
		Vector3<T> xaxis = Vector3<T>::normalize(Vector3<T>::cross_product(up, zaxis));
		Vector3<T> yaxis = Vector3<T>::cross_product(zaxis, xaxis);


		result[0][0] = xaxis[0];			result[0][1] = yaxis[0];			result[0][2] = zaxis[0];			result[0][3] = 0;
		result[1][0] = xaxis[1];			result[1][1] = yaxis[1];			result[1][2] = zaxis[1];			result[1][3] = 0;
		result[2][0] = xaxis[2];			result[2][1] = yaxis[2];			result[2][2] = zaxis[2];			result[2][3] = 0;
		result[3][0] = -Vector3<T>::dot_product(xaxis, eye);	result[3][1] = -Vector3<T>::dot_product(yaxis, eye);	result[3][2] = -Vector3<T>::dot_product(zaxis, eye);	result[3][3] = 1;

		return result;
	}

	inline static Matrix4x4<T> get_lookAtLH(Vector3<T> eye, Vector3<T> at, Vector3<T> up)
	{
		Matrix4x4<T> result;

		Vector3<T> zaxis = Vector3<T>::normalize(at - eye);
		Vector3<T> xaxis = Vector3<T>::normalize(Vector3<T>::cross_product(up, zaxis));
		Vector3<T> yaxis = Vector3<T>::cross_product(zaxis, xaxis);


		result[0][0] = xaxis[0];								result[0][1] = yaxis[0];								result[0][2] = zaxis[0];								result[0][3] = 0;
		result[1][0] = xaxis[1];								result[1][1] = yaxis[1];								result[1][2] = zaxis[1];								result[1][3] = 0;
		result[2][0] = xaxis[2];								result[2][1] = yaxis[2];								result[2][2] = zaxis[2];								result[2][3] = 0;
		result[3][0] = -Vector3<T>::dot_product(xaxis, eye);	result[3][1] = -Vector3<T>::dot_product(yaxis, eye);	result[3][2] = -Vector3<T>::dot_product(zaxis, eye);	result[3][3] = 1;

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

	inline static Matrix4x4<T> set_pos(const Vector3<T>& pos, const Matrix4x4<T>& mat) {

		Matrix4x4<T> result = mat;

		result[3][0] = pos[0];
		result[3][1] = pos[1];
		result[3][2] = pos[2];

		return result;
	}

	inline static Matrix4x4<T> invert(const Matrix4x4<T>& mat) {

		Matrix4x4<T> M = Matrix4x4<T>::get_identity();

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				M[i][j] = mat[j][i];

		M = Matrix4x4<T>::set_pos(-(M*Matrix4x4<T>::getPos(mat)), M);

		return M;

	}

	inline void set(unsigned int x, unsigned int y, T val) { m[x][y] = val; }
	inline T get(unsigned int x, unsigned int y) { return m[x][y]; }

	inline const T* operator[](int index) const { return m[index]; }
	inline T* operator[](int index) { return m[index]; }
};

typedef Matrix4x4<float> Matrix4f;