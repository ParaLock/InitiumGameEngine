#pragma once
#include "../../../sysInclude.h"

class Transform
{
private:
	Vector3f _pos;

	D3DXMATRIX _transformMatrix;
	D3DXMATRIX _transposedTransformMatrix;
public:
	Transform();
	~Transform();

	void setRotation(float angleOfRot, std::string direction);
	void setPos(Vector3f pos);

	D3DXMATRIX& getTransformMatrix() { return _transformMatrix; };

	D3DXMATRIX& getTransposedTransformMatrix() {

		D3DXMatrixTranspose(&_transposedTransformMatrix, &_transformMatrix);

		return _transposedTransformMatrix;
	}
};

