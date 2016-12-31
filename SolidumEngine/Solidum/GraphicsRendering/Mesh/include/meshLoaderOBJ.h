#pragma once

#include "meshLoader.h"
#include "mesh.h"

#ifndef _MESHLDR_OBJ
#define _MESHLDR_OBJ

class meshLoaderOBJ : public meshLoader
{
private:
	void parseMesh();

	bool IS_QUAD;

public:
	meshLoaderOBJ();
	~meshLoaderOBJ();

	void loadMesh(LPCWSTR fileName, mesh *mesh);
};

#endif