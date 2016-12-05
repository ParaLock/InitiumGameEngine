#pragma once

#include "../../../sysInclude.h"

#ifndef _MESHLDR_H
#define _MESHLDR_H

class mesh;

class meshLoader
{
private:
	virtual void parseMesh() = 0;
public:
	meshLoader();
	virtual ~meshLoader();

	virtual void loadMesh(LPCWSTR fileName, mesh *mesh) = 0;
};

#endif