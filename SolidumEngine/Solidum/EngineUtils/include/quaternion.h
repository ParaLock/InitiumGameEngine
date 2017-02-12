#pragma once

template<typename T>
class Quaternion : public Vector4<T>
{
private:
public:
	Quaternion(T x = 0.0f, T y = 0.0f, T z = 0.0f, T w = 1.0f)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}

	Quaternion(const Vector4<T>& r)
	{
		d[0] = r[0];
		d[1] = r[1];
		d[2] = r[2];
		d[3] = r[3];
	}

	Quaternion(const Vector3<T>& axis, float angle)
	{
		float sinHalfAngle = sinf(angle / 2);
		float cosHalfAngle = cosf(angle / 2);

		d[0] = axis.GetX() * sinHalfAngle;
		d[1] = axis.GetY() * sinHalfAngle;
		d[2] = axis.GetZ() * sinHalfAngle;
		d[3] = cosHalfAngle;
	}

	Quaternion(const Matrix4x4<T>& m)
	{
		T trace = m[0][0] + m[1][1] + m[2][2];

		if (trace > 0)
		{
			T s = 0.5f / sqrtf(trace + 1.0f);
			d[3] = 0.25f / s;
			d[0] = (m[1][2] - m[2][1]) * s;
			d[1] = (m[2][0] - m[0][2]) * s;
			d[2] = (m[0][1] - m[1][0]) * s;
		}
		else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
		{
			T s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
			d[3] = (m[1][2] - m[2][1]) / s;
			d[0] = 0.25f * s;
			d[1] = (m[1][0] + m[0][1]) / s;
			d[2] = (m[2][0] + m[0][2]) / s;
		}
		else if (m[1][1] > m[2][2])
		{
			T s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
			d[3] = (m[2][0] - m[0][2]) / s;
			d[0] = (m[1][0] + m[0][1]) / s;
			d[1] = 0.25f * s;
			d[2] = (m[2][1] + m[1][2]) / s;
		}
		else
		{
			T s = 2.0f * sqrtf(1.0f + m[2][2] - m[1][1] - m[0][0]);
			d[3] = (m[0][1] - m[1][0]) / s;
			d[0] = (m[2][0] + m[0][2]) / s;
			d[1] = (m[1][2] + m[2][1]) / s;
			d[2] = 0.25f * s;
		}

		T length = Vector4<T>::length(Vector4<T>(d[0], d[1], d[2], d[3]));
		d[3] = d[3] / length;
		d[0] = d[0] / length;
		d[1] = d[1] / length;
		d[2] = d[2] / length;
	}

	inline static Quaternion<T> NLerp(const Quaternion<T>& q1, const Quaternion<T>& q2, float lerpFactor, bool shortestPath)
	{
		Quaternion<T> correctedDest;

		if (shortestPath && dot_product(q1, q2) < 0)
			correctedDest = q1 * -1;
		else
			correctedDest = q1;

		return Quaternion<T>(Lerp(correctedDest, lerpFactor).Normalized());
	}

	inline static Quaternion<T> SLerp(const Quaternion<T>& q1, const Quaternion<T>& q2, float lerpFactor, bool shortestPath)
	{
		static const float EPSILON = 1e3;

		float cos = dot_product(q1, q2);
		Quaternion<T> correctedDest;

		if (shortestPath && cos < 0)
		{
			cos *= -1;
			correctedDest = q1 * -1;
		}
		else
			correctedDest = q1;

		if (fabs(cos) >(1 - EPSILON))
			return NLerp(correctedDest, lerpFactor, false);

		float sin = (float)sqrtf(1.0f - cos * cos);
		float angle = atan2(sin, cos);
		float invSin = 1.0f / sin;

		float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
		float destFactor = sinf((lerpFactor)* angle) * invSin;

		return Quaternion<T>((*this) * srcFactor + correctedDest * destFactor);
	}

	inline static Matrix4x4<T> to_rotation_matrix(const Quaternion<T>& q)
	{

		Vector3<T> forwarq = Vector3<T>(2.0f * (q[0] * q[2] - q[3] * q[1]), 2.0f * (q[1] * q[2] + q[3] * q[0]), 1.0f - 2.0f * (q[0] * q[0] + q[1] * q[1]));
		Vector3<T> up = Vector3<T>(2.0f * (q[0] * q[1] + q[3] * q[2]), 1.0f - 2.0f * (q[0] * q[0] + q[2] * q[2]), 2.0f * (q[1] * q[2] - q[3] * q[0]));
		Vector3<T> right = Vector3<T>(1.0f - 2.0f * (q[1] * q[1] + q[2] * q[2]), 2.0f * (q[0] * q[1] - q[3] * q[2]), 2.0f * (q[0] * q[2] + q[3] * q[1]));

		return Matrix4x4<T>::rotation_from_vectors(forward, up, right);
	}

	inline Vector3<T> GetForward() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(0, 0, 1));
	}

	inline Vector3<T> GetBack() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(0, 0, -1));
	}

	inline Vector3<T> GetUp() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(0, 1, 0));
	}

	inline Vector3<T> GetDown() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(0, -1, 0));
	}

	inline Vector3<T> GetRight() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(1, 0, 0));
	}

	inline Vector3<T> GetLeft() const
	{
		return Vector3<T>::rotate((*this), Vector3<T>(-1, 0, 0));
	}

	inline static Quaternion<T> conjugate(const Quaternion<T>& q) { return Quaternion<T>(-q[0], -q[1], -q[2], q[3]); }

	inline Quaternion<T> operator*(const Quaternion<T>& r)
	{
		const T _w = (d[3] * r[3]) - (d[0] * r[0]) - (d[1] * r[1]) - (d[2] * r[2]);
		const T _x = (d[0] * r[3]) + (d[3] * r[0]) + (d[1] * r[2]) - (d[2] * r[1]);
		const T _y = (d[1] * r[3]) + (d[3] * r[1]) + (d[2] * r[0]) - (d[0] * r[2]);
		const T _z = (d[2] * r[3]) + (d[3] * r[2]) + (d[0] * r[1]) - (d[1] * r[0]);

		return Quaternion<T>(_x, _y, _z, _w);
	}

	inline Quaternion<T> operator*(const Vector3<T>& v)
	{
		const T _w = -(d[0] * v[0]) - (d[1] * v[1]) - (d[2] * v[2]);
		const T _x = (d[3] * v[0]) + (d[1] * v[2]) - (d[2] * v[1]);
		const T _y = (d[3] * v[1]) + (d[2] * v[0]) - (d[0] * v[2]);
		const T _z = (d[3] * v[2]) + (d[0] * v[1]) - (d[1] * v[0]);

		return Quaternion(_x, _y, _z, _w);
	}
};