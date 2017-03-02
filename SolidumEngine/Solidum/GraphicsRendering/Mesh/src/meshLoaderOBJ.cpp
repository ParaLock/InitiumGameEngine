#include "../include/meshLoaderOBJ.h"


meshLoaderOBJ::meshLoaderOBJ()
{
}


meshLoaderOBJ::~meshLoaderOBJ()
{
}

void meshLoaderOBJ::parseMesh()
{
}

void meshLoaderOBJ::loadMesh(LPCWSTR fileName, mesh *mesh)
{
	std::ifstream file(fileName);

	std::vector<std::string*> line;

	std::vector<Vector3f> temp_vertices;
	std::vector<Vector3f> temp_normals;
	std::vector<Vector2f> temp_texCoords;

	std::vector<Vector3f> expanded_vertices;
	std::vector<Vector3f> expanded_normals;
	std::vector<Vector2f> expanded_texCoords;

	std::vector<Vector3f> final_vertices;
	std::vector<Vector3f> final_normals;
	std::vector<Vector2f> final_texCoords;

	std::vector<Vector3f> expanded_biNormals;
	std::vector<Vector3f> expanded_tangents;

	std::vector<Vector3f> final_biNormals;
	std::vector<Vector3f> final_tangents;

	std::vector<unsigned short> final_indices;

	std::vector<DWORD> verticeIndex;
	std::vector<DWORD> normalsIndex;
	std::vector<DWORD> texCoordsIndex;

	int indice_1;
	int indice_2;
	int indice_3;

	int texCoordIndex_1;
	int texCoordIndex_2;
	int texCoordIndex_3;

	int normalIndex_1;
	int normalIndex_2;
	int normalIndex_3;

	int indexCount = 0;

	if (!file.is_open())
	{
		printf("Mesh file open failed!\n");
	}
	else {
		char buf[256];

		float res_1 = 0;
		float res_2 = 0;
		float res_3 = 0;
		float res_4 = 0;

		while (!file.eof())
		{
			file.getline(buf, 256);

			if(buf[0] != 0)
			line.push_back(new std::string(buf));
		}

		for (size_t i = 0; i < line.size(); i++) {

			if (line.at(i)->at(0) == '#') {
				continue;
			}

			if (line.at(i)->at(0) == 'v' && line.at(i)->at(1) == ' ') {

				sscanf_s(line.at(i)->c_str(), "v %f %f %f", &res_1, &res_2, &res_3);

				Vector3f vecTemp = {res_1, res_2, res_3};

				temp_vertices.push_back(vecTemp);

			}

			if (line.at(i)->at(0) == 'v' && line.at(i)->at(1) == 't') {

				sscanf_s(line.at(i)->c_str(), "vt %f %f", &res_1, &res_2);

				Vector2f normTemp = {res_1, res_2};

				temp_texCoords.push_back(normTemp);
			}

			if (line.at(i)->at(0) == 'v' && line.at(i)->at(1) == 'n') {

				sscanf_s(line.at(i)->c_str(), "vn %f %f %f", &res_1, &res_2, &res_3);

				Vector3f normTemp = { res_1, res_2, res_3 };

				temp_normals.push_back(normTemp);

			}

			if (line.at(i)->at(0) == 'f') {

				if (std::count(line.at(i)->begin(), line.at(i)->end(), ' ') == 4) {

					printf("Quad Meshes Not Supported!\n");

					break;
				}

				sscanf_s(line.at(i)->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&indice_1, &texCoordIndex_1, &normalIndex_1,
					&indice_2, &texCoordIndex_2, &normalIndex_2,
					&indice_3, &texCoordIndex_3, &normalIndex_3);

				verticeIndex.push_back(indice_1);
				verticeIndex.push_back(indice_2);
				verticeIndex.push_back(indice_3);

				texCoordsIndex.push_back(texCoordIndex_1);
				texCoordsIndex.push_back(texCoordIndex_2);
				texCoordsIndex.push_back(texCoordIndex_3);

				normalsIndex.push_back(normalIndex_1);
				normalsIndex.push_back(normalIndex_2);
				normalsIndex.push_back(normalIndex_3);

			}
		}

		mesh->meshSize = verticeIndex.size() * sizeof(VERTEX);
		mesh->indicesSize = verticeIndex.size() * sizeof(DWORD);

		mesh->numIndices = verticeIndex.size();

		mesh->meshIndices = new DWORD[mesh->indicesSize];
		mesh->meshVertices = new VERTEX[mesh->meshSize];

		for (int i = 0; i < verticeIndex.size(); i++) {

			DWORD vertexIndex = verticeIndex[i];
			DWORD uvIndex = texCoordsIndex[i];
			DWORD normalIndex = normalsIndex[i];

			Vector3f vertex = temp_vertices[vertexIndex - 1];
			Vector2f uv = temp_texCoords[uvIndex - 1];
			Vector3f normal = temp_normals[normalIndex - 1];

			expanded_vertices.push_back(vertex);
			expanded_texCoords.push_back(uv);
			expanded_normals.push_back(normal);
		}

		mesh->calcTangentsAndBiNormals(expanded_vertices, expanded_texCoords,
			expanded_normals, expanded_tangents, expanded_biNormals);


		mesh->calcMeshIndices(expanded_vertices, expanded_texCoords, expanded_normals, 
			expanded_tangents, expanded_biNormals, final_indices, final_vertices, final_texCoords, final_normals, final_tangents, final_biNormals);
	
		mesh->numVertices = final_vertices.size();

		for (int i = 0; i < mesh->numVertices; i++) {

			mesh->meshVertices[i].Pos = final_vertices[i];
			mesh->meshVertices[i].Normal = final_normals[i];
			mesh->meshVertices[i].TexCoords = final_texCoords[i];
			mesh->meshVertices[i].Tangent = final_tangents[i];
			mesh->meshVertices[i].biNormal = final_biNormals[i];
		}

		for (int i = 0; i < final_indices.size(); i++)
			mesh->meshIndices[i] = final_indices[i];
	}
}

