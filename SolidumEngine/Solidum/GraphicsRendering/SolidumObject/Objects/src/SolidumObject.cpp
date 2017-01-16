#include "../include/SolidumObject.h"



SolidumObject::SolidumObject(IResourceBuilder* builder)
{
	_transform = new Transform();
}


SolidumObject::~SolidumObject()
{
}

void SolidumObject::attachMesh(mesh* newMesh)
{
	_mesh = newMesh;
}

void SolidumObject::attachMaterial(Material* newMat)
{
	_mat = newMat;
}

void SolidumObject::attachShader(Shader* newShader)
{
	_shader = newShader;
}

void SolidumObject::attachTexture(Texture * tex)
{
	_tex = tex;
}

void SolidumObject::draw()
{
	if (_shader != nullptr) {
		if (_transform != nullptr) {
			_shader->updateModelUniforms(_transform);
		}
		if (_mat != nullptr) {
			_shader->updateMaterialUniforms(_mat);
		}
		if (_mesh != nullptr) {
			_shader->setMesh(_mesh);
		}

		if (_tex != nullptr) {
			_shader->setModelTexture(_tex);
		}

		_shader->updateGPU();

		if (_mesh != nullptr) {
			_shader->execute(_mesh->numIndices);
		}
		else {
			_shader->execute(NULL);
		}
	}
}
