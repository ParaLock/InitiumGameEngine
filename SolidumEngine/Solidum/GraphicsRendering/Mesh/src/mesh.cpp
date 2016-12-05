#include "..\include\mesh.h"



mesh::mesh(LPCWSTR fileName, std::shared_ptr<meshLoader> ldr)
{
	ldr->loadMesh(fileName, this);

	indexBuff = GraphicsBufferFactory::createBuffer(DXBUFFER_TYPE_INDEX, indicesSize);
	vertexBuff = GraphicsBufferFactory::createBuffer(DXBUFFER_TYPE_VERTEX, meshSize);

	indexBuff->Write(meshIndices, indicesSize, 0);
	vertexBuff->Write(meshVertices, meshSize, 0);
}

mesh::~mesh()
{
	delete indexBuff;
	delete vertexBuff;
}

void mesh::draw()
{
	indexBuff->Bind();
	vertexBuff->Bind();
}
