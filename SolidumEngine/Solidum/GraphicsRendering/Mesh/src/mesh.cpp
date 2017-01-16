#include "..\include\mesh.h"



mesh::mesh(IResourceBuilder *builder)
{
	meshBuilder* realBuilder = static_cast<meshBuilder*>(builder);

	LPCWSTR fileName = realBuilder->_filename;

	if (fileName == L"gen_ortho_window_mesh") {
		generateOrthoWindowMesh(realBuilder);
	}
	else {
		std::shared_ptr<meshLoader> pMeshLoader;

		std::string stlStr = CW2A(fileName);

		std::vector<std::string> splitFilename = StringManipulation::split(&stlStr, '.');

		pMeshLoader = std::shared_ptr<meshLoaderOBJ>(new meshLoaderOBJ());
		

		pMeshLoader->loadMesh(fileName, this);

		IResourceBuilder* indexBuffBuilder = new GPUBufferBuilder(indicesSize, BUFFER_TYPE::INDEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);
		IResourceBuilder* vertexBuffBuilder = new GPUBufferBuilder(meshSize, BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

		_indexBuff = realBuilder->_managerPool->getResourceManager("GPUBufferManager")
			->createResource(indexBuffBuilder, stlStr + "index_buffer")->getCore<GPUBuffer>();

		_vertexBuff = realBuilder->_managerPool->getResourceManager("GPUBufferManager")
			->createResource(vertexBuffBuilder, stlStr + "vertex_buffer")->getCore<GPUBuffer>();

		_indexBuff->getCore<GPUBuffer>()->Write(meshIndices, indicesSize, 0);
		_vertexBuff->getCore<GPUBuffer>()->Write(meshVertices, meshSize, 0);
	}
}

mesh::~mesh()
{
}

void mesh::generateOrthoWindowMesh(meshBuilder* builder)
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

	GPUBufferBuilder indexBuffBuilder(m_indexCount * sizeof(unsigned long), BUFFER_TYPE::INDEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);
    GPUBufferBuilder vertexBuffBuilder(m_vertexCount * sizeof(LIGHT_VERTEX), BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

	std::string stlStr = CW2A(builder->_filename);

	_indexBuff = builder->_managerPool->getResourceManager("GPUBufferManager")
		->createResource(&indexBuffBuilder, stlStr + "index_buffer")->getCore<GPUBuffer>();

	_vertexBuff = builder->_managerPool->getResourceManager("GPUBufferManager")
		->createResource(&vertexBuffBuilder, stlStr + "vertex_buffer")->getCore<GPUBuffer>();


	_indexBuff->getCore<GPUBuffer>()->Write(indices, m_indexCount * sizeof(unsigned long), 0);
	_vertexBuff->getCore<GPUBuffer>()->Write(vertices, m_vertexCount * sizeof(LIGHT_VERTEX), 0);

	delete[] vertices;
	vertices = 0;


	delete[] indices;
	indices = 0;

	numIndices = 6;
	meshSize = m_vertexCount * sizeof(LIGHT_VERTEX);
}