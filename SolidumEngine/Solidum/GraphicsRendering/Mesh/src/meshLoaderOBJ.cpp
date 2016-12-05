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

	std::vector<std::string*> *line = new std::vector<std::string*>;

	std::vector<D3DXVECTOR3> *vertices = new std::vector<D3DXVECTOR3>;
	std::vector<D3DXVECTOR3> *normals = new std::vector<D3DXVECTOR3>;
	std::vector<D3DXVECTOR2> *texCoords = new std::vector<D3DXVECTOR2>;

	std::vector<DWORD> *verticeIndex = new std::vector<DWORD>;
	std::vector<DWORD> *normalsIndex = new std::vector<DWORD>;
	std::vector<DWORD> *texCoordsIndex = new std::vector<DWORD>;

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
			line->push_back(new std::string(buf));
		}

		for (size_t i = 0; i < line->size(); i++) {

			if (line->at(i)->at(0) == '#') {
				continue;
			}

			if (line->at(i)->at(0) == 'v' && line->at(i)->at(1) == ' ') {

				sscanf_s(line->at(i)->c_str(), "v %f %f %f", &res_1, &res_2, &res_3);

				D3DXVECTOR3 vecTemp = {res_1, res_2, res_3};

				vertices->push_back(vecTemp);

			}

			if (line->at(i)->at(0) == 'v' && line->at(i)->at(1) == 't') {

				sscanf_s(line->at(i)->c_str(), "vt %f %f", &res_1, &res_2);

				D3DXVECTOR2 normTemp = {res_1, res_2};

				texCoords->push_back(normTemp);
			}

			if (line->at(i)->at(0) == 'v' && line->at(i)->at(1) == 'n') {

				sscanf_s(line->at(i)->c_str(), "vn %f %f %f", &res_1, &res_2, &res_3);

				D3DXVECTOR3 normTemp = { res_1, res_2, res_3 };

				normals->push_back(normTemp);

			}

			if (line->at(i)->at(0) == 'f') {

				if (std::count(line->at(i)->begin(), line->at(i)->end(), ' ') == 4) {

					printf("Quad Meshes Not Supported!\n");
					break;

				}

				sscanf_s(line->at(i)->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&indice_1, &texCoordIndex_1, &normalIndex_1,
					&indice_2, &texCoordIndex_2, &normalIndex_2,
					&indice_3, &texCoordIndex_3, &normalIndex_3);

				verticeIndex->push_back(indice_1 - 1);
				verticeIndex->push_back(indice_2 - 1);
				verticeIndex->push_back(indice_3 - 1);

				texCoordsIndex->push_back(texCoordIndex_1 - 1);
				texCoordsIndex->push_back(texCoordIndex_2 - 1);
				texCoordsIndex->push_back(texCoordIndex_3 - 1);

				normalsIndex->push_back(normalIndex_1 - 1);
				normalsIndex->push_back(normalIndex_2 - 1);
				normalsIndex->push_back(normalIndex_3 - 1);

			}

			if (line->at(i)->at(0) == 'u' && line->at(i)->at(1) == 's' && line->at(i)->at(2) == 'e') {

			}
		}

		mesh->meshSize = verticeIndex->size() * sizeof(VERTEX);
		mesh->indicesSize = verticeIndex->size() * sizeof(DWORD);

		mesh->numIndices = verticeIndex->size();

		mesh->meshIndices = new DWORD[mesh->indicesSize];
		mesh->meshVertices = new VERTEX[mesh->meshSize];

		std::map<std::tuple<int, int, int>, int> indexMap;

		for (size_t i = 0; i < verticeIndex->size(); i++) {

			indexMap[std::make_tuple(verticeIndex->at(i), texCoordsIndex->at(i), normalsIndex->at(i))] = i;
			mesh->meshIndices[i] = indexMap[std::make_tuple(verticeIndex->at(i), texCoordsIndex->at(i), normalsIndex->at(i))];
		}

		for (size_t i = 0; i < verticeIndex->size(); i++) {

			mesh->meshVertices[i].Pos = vertices->at(verticeIndex->at(i));
			mesh->meshVertices[i].Normal = normals->at(normalsIndex->at(i));
			mesh->meshVertices[i].TexCoords = texCoords->at(texCoordsIndex->at(i));

		}

		delete line;
		delete vertices;
		delete normals;
		delete texCoords;

		delete texCoordsIndex;
		delete normalsIndex;
		delete verticeIndex;
	}
}

