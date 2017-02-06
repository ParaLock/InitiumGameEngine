#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class Transform : public IResource
{
private:
	Vector3f _pos;

	D3DXMATRIX _transformMatrix;
	D3DXMATRIX _transposedTransformMatrix;
public:
	Transform();
	~Transform();

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void setRotation(float angleOfRot, std::string direction);
	void setPos(Vector3f pos);

	void setTransformMatrix(D3DXMATRIX& matrix) { _transformMatrix = matrix; }

	D3DXMATRIX& getTransformMatrix() { return _transformMatrix; };

	D3DXMATRIX& getTransposedTransformMatrix() {

		D3DXMatrixTranspose(&_transposedTransformMatrix, &_transformMatrix);

		return _transposedTransformMatrix;
	}

	Vector3f getPos() { return _pos; }
};

