#pragma once
#include "../../../sysInclude.h"



class Transform
{
private:
	D3DXVECTOR3 pos;
	D3DXMATRIX objMatrix;

	Transform *parent = NULL;
public:
	Transform();
	~Transform();

	void setParent(Transform *newParent) { parent = newParent; };

	void setRotation(float angleOfRot, std::string direction);
	void setPos(float x, float y, float z);

	D3DXMATRIX& getTransform() { return objMatrix; };

	D3DXMATRIX& getParentTransform() { if (parent != NULL) return parent->getTransform(); };
};

