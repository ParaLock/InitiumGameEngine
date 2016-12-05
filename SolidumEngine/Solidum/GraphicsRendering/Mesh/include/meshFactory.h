#pragma once
#include "meshLoader.h"
#include "mesh.h"

#include "../../../sysInclude.h"

class meshFactory
{
private:
	static std::map<std::string, mesh*> *meshLibrary;
public:
	meshFactory();
	~meshFactory();

	static mesh* createMesh(LPCWSTR filename, std::shared_ptr<meshLoader> ldr, std::string ID);

	static mesh* requestMesh(std::string ID);

	static void destroyLibrary();
};

