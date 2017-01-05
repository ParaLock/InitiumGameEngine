#include "..\include\mesh.h"



mesh::mesh(LPCWSTR fileName, std::shared_ptr<meshLoader> ldr)
{
	if (fileName == L"gen_ortho_window_mesh") {
		generateOrthoWindowMesh();
	}
	else {

		ldr->loadMesh(fileName, this);

		_indexBuff = GPUBufferFactory::createBuffer(indicesSize, BUFFER_TYPE::INDEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);
		_vertexBuff = GPUBufferFactory::createBuffer(meshSize, BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

		_indexBuff->Write(meshIndices, indicesSize, 0);
		_vertexBuff->Write(meshVertices, meshSize, 0);
	}
}

mesh::~mesh()
{
	delete _indexBuff;
	delete _indexBuff;
}

void mesh::setActiveTexture(Texture * newTex)
{
	_pActiveTexture = newTex;
}

void mesh::setActiveShader(Shader * newShader)
{
	_pActiveShader = newShader;
}


void mesh::generateOrthoWindowMesh()
{
	int screen_width = windowAccessor::screen_width;
	int screen_height = windowAccessor::screen_height;

	int m_vertexCount, m_indexCount;

	float left, right, top, bottom;

	LIGHT_VERTEX* vertices;

	unsigned long* indices;

	int i;

	left = (float)((screen_width / 2) * -1);
	right = left + (float)screen_width;
	top = (float)(screen_height / 2);
	bottom = top - (float)screen_height;

	m_vertexCount = 6;
	m_indexCount = m_vertexCount;

	vertices = new LIGHT_VERTEX[m_vertexCount];

	indices = new unsigned long[m_indexCount];

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	for (i = 0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	_indexBuff = GPUBufferFactory::createBuffer(m_indexCount * sizeof(unsigned long), BUFFER_TYPE::INDEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);
	_vertexBuff = GPUBufferFactory::createBuffer(m_vertexCount * sizeof(LIGHT_VERTEX), BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

	_indexBuff->Write(indices, m_indexCount * sizeof(unsigned long), 0);
	_vertexBuff->Write(vertices, m_vertexCount * sizeof(LIGHT_VERTEX), 0);

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	numIndices = 6;
	meshSize = m_vertexCount * sizeof(LIGHT_VERTEX);
}


void mesh::draw()
{
	if (_pActiveShader != nullptr) {

		_pActiveShader->updateGPU();

		if(_indexBuff != nullptr && _vertexBuff != nullptr)
		_pActiveShader->setMeshBuffers(_indexBuff, _vertexBuff, "null");

		if(_pActiveTexture != nullptr)
		_pActiveShader->setTexture(_pActiveTexture);

		_pActiveShader->execute(numIndices);
	}
}
