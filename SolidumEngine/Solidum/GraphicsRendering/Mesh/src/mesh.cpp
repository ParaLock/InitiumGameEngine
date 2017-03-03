#include "..\include\mesh.h"



mesh::mesh()
{
}

mesh::~mesh()
{
}

void mesh::load(IResourceBuilder *builder)
{
	meshBuilder *realBuilder = static_cast<meshBuilder*>(builder);

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
			->createResource(indexBuffBuilder, stlStr + "index_buffer", false)->getCore<GPUBuffer>();

		_vertexBuff = realBuilder->_managerPool->getResourceManager("GPUBufferManager")
			->createResource(vertexBuffBuilder, stlStr + "vertex_buffer", false)->getCore<GPUBuffer>();

		_indexBuff->getCore<GPUBuffer>()->Write(meshIndices, indicesSize, 0);
		_vertexBuff->getCore<GPUBuffer>()->Write(meshVertices, meshSize, 0);
	}

	isLoaded = true;
}

void mesh::unload()
{
}

bool mesh::is_near(float v1, float v2)
{
	return fabs(v1 - v2) < 0.01f;
}

bool mesh::getSimilarVertexIndex(
	Vector3f & in_vertex,
	Vector2f & in_uv,
	Vector3f & in_normal,
	std::vector<Vector3f> & out_vertices,
	std::vector<Vector2f> & out_uvs,
	std::vector<Vector3f> & out_normals,
	unsigned short & result)
{
	// Lame linear search
	for (unsigned int i = 0; i<out_vertices.size(); i++) {
		if (

			is_near(in_vertex[0], out_vertices[i][0]) &&
			is_near(in_vertex[1], out_vertices[i][1]) &&
			is_near(in_vertex[2], out_vertices[i][2]) &&
			is_near(in_uv[0], out_uvs[i][0]) &&
			is_near(in_uv[1], out_uvs[i][1]) &&
			is_near(in_normal[0], out_normals[i][0]) &&
			is_near(in_normal[1], out_normals[i][1]) &&
			is_near(in_normal[2], out_normals[i][2])
			) {
			result = i;
			return true;
		}
	}

	return false;
}

void mesh::calcMeshIndices(
	std::vector<Vector3f> & in_vertices,
	std::vector<Vector2f> & in_uvs,
	std::vector<Vector3f> & in_normals,
	std::vector<Vector3f> & in_tangents,
	std::vector<Vector3f> & in_bitangents,

	std::vector<unsigned short> & out_indices,
	std::vector<Vector3f> & out_vertices,
	std::vector<Vector2f> & out_uvs,
	std::vector<Vector3f> & out_normals,
	std::vector<Vector3f> & out_tangents,
	std::vector<Vector3f> & out_bitangents
	)
{
	for (unsigned int i = 0; i<in_vertices.size(); i++) {

		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found) {
			out_indices.push_back(index);

			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else { 
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}

void mesh::calcTangentsAndBiNormals(
	std::vector<Vector3f> & vertices,
	std::vector<Vector2f> & uvs,
	std::vector<Vector3f> & normals,

	std::vector<Vector3f> & tangents,
	std::vector<Vector3f> & bitangents
	)
{
	for (int i = 0; i < vertices.size(); i += 3) {

		Vector3f & v0 = vertices[i + 0];
		Vector3f & v1 = vertices[i + 1];
		Vector3f & v2 = vertices[i + 2];

		Vector2f & uv0 = uvs[i + 0];
		Vector2f & uv1 = uvs[i + 1];
		Vector2f & uv2 = uvs[i + 2];

		Vector3f deltaPos1 = v1 - v0;
		Vector3f deltaPos2 = v2 - v0;

		Vector2f deltaUV1 = uv1 - uv0;
		Vector2f deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1[0] * deltaUV2[1] - deltaUV1[1] * deltaUV2[0]);
		
		Vector3f tangent = (deltaPos1 * deltaUV2[1] - deltaPos2 * deltaUV1[1])*r;
		
		Vector3f bitangent = (deltaPos2 * deltaUV1[0] - deltaPos1 * deltaUV2[0])*r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
	}

	int debugRef = -1;
}


void mesh::generateOrthoWindowMesh(meshBuilder* builder)
{

	int screen_width = window::getInstance()->screen_width;
	int screen_height = window::getInstance()->screen_height;

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

	vertices[0].position = Vector3f(left, top, 0.0f);
	vertices[0].texture = Vector2f(0.0f, 0.0f);

	vertices[1].position = Vector3f(right, bottom, 0.0f);
	vertices[1].texture = Vector2f(1.0f, 1.0f);

	vertices[2].position = Vector3f(left, bottom, 0.0f);
	vertices[2].texture = Vector2f(0.0f, 1.0f);

	vertices[3].position = Vector3f(left, top, 0.0f);
	vertices[3].texture = Vector2f(0.0f, 0.0f);

	vertices[4].position = Vector3f(right, top, 0.0f);
	vertices[4].texture = Vector2f(1.0f, 0.0f);

	vertices[5].position = Vector3f(right, bottom, 0.0f);
	vertices[5].texture = Vector2f(1.0f, 1.0f);

	for (i = 0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	GPUBufferBuilder indexBuffBuilder(m_indexCount * sizeof(unsigned long), BUFFER_TYPE::INDEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);
    GPUBufferBuilder vertexBuffBuilder(m_vertexCount * sizeof(LIGHT_VERTEX), BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

	std::string stlStr = CW2A(builder->_filename);

	_indexBuff = builder->_managerPool->getResourceManager("GPUBufferManager")
		->createResource(&indexBuffBuilder, stlStr + "index_buffer", false)->getCore<GPUBuffer>();

	_vertexBuff = builder->_managerPool->getResourceManager("GPUBufferManager")
		->createResource(&vertexBuffBuilder, stlStr + "vertex_buffer", false)->getCore<GPUBuffer>();


	_indexBuff->getCore<GPUBuffer>()->Write(indices, m_indexCount * sizeof(unsigned long), 0);
	_vertexBuff->getCore<GPUBuffer>()->Write(vertices, m_vertexCount * sizeof(LIGHT_VERTEX), 0);

	delete[] vertices;
	vertices = 0;


	delete[] indices;
	indices = 0;

	numIndices = 6;
	meshSize = m_vertexCount * sizeof(LIGHT_VERTEX);
}