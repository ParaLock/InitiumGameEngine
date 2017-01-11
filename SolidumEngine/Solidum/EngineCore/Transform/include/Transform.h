#pragma once
#include "../../../sysInclude.h"

class Transform
{
private:
	Vector3f _pos;

	D3DXMATRIX _transformMatrix;
	D3DXMATRIX _transposedTransformMatrix;

	Transform *parent = NULL;
public:
	Transform();
	~Transform();

	void setParent(Transform *newParent) { parent = newParent; };

	void setRotation(float angleOfRot, std::string _transformMatrix);
	void setPos(Vector3f pos);

	D3DXMATRIX& getTransform() { return _transformMatrix; };

	D3DXMATRIX& getTransposedTransform() {

		D3DXMatrixTranspose(&_transposedTransformMatrix, &_transformMatrix);

		return _transposedTransformMatrix;
	}

	D3DXMATRIX& getParent() { if (parent != NULL) return parent->getTransform(); };
};

