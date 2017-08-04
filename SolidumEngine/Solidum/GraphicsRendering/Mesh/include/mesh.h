#pragma once

#include "meshLoader.h"
#include "meshLoaderOBJ.h"
#include "../../../sysInclude.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

#include "../../GraphicsBuffers/include/GPUBuffer.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../../ResourceFramework/include/ResourceInitParams.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../ResourceFramework/include/ResourceCreator.h"

#include "../../ActiveGraphicsAPI.h"

class GenericFactory;

class ResourcePool;

class mesh : public Resource<mesh, GenericFactory, ResourcePool>
{
private:
	IResource* _vertexBuff;
	IResource* _indexBuff;

public:
	mesh();
	~mesh();

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		LPCWSTR _filename;

		ResourceCreator* _resourceCreator;

		InitData(LPCWSTR filename, ResourceCreator* resCreator) :
			_resourceCreator(resCreator)
		{
			_filename = filename;
		}
	};

	void generatePlaneMesh(float top, float bottom, float left, float right, ResourceCreator* resCreator);

	void load();
	void unload();

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	int meshSize;
	int indicesSize;

	int numVertices;
	int numIndices;

	bool is_near(float v1, float v2);

	bool getSimilarVertexIndex(
		Vector3f & in_vertex,
		Vector2f & in_uv,
		Vector3f & in_normal,
		std::vector<Vector3f> & out_vertices,
		std::vector<Vector2f> & out_uvs,
		std::vector<Vector3f> & out_normals,
		unsigned short & result
		);



	void calcMeshIndices(
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
		);

	void calcTangentsAndBiNormals(
		std::vector<Vector3f> & vertices,
		std::vector<Vector2f> & uvs,
		std::vector<Vector3f> & normals,
		
		std::vector<Vector3f> & tangents,
		std::vector<Vector3f> & bitangents
		);

	VERTEX *meshVertices;
	DWORD *meshIndices;
	
	GPUBuffer* getVertexBuff() { return (GPUBuffer*)_vertexBuff; }
	GPUBuffer* getIndexBuff() { return (GPUBuffer*)_indexBuff; }
protected:
};
