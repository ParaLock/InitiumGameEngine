#include "../include/meshFactory.h"



meshFactory::meshFactory()
{
}


meshFactory::~meshFactory()
{
}

std::map<std::string, mesh*>* meshFactory::meshLibrary = new std::map<std::string, mesh*>;

mesh * meshFactory::createMesh(LPCWSTR filename, std::shared_ptr<meshLoader> ldr, std::string ID)
{
	mesh* newMesh = new mesh(filename, ldr);

	meshLibrary->insert({ID, newMesh});

	return newMesh;
}

mesh * meshFactory::requestMesh(std::string ID)
{
	return meshLibrary->at(ID);
}

void meshFactory::destroyLibrary()
{
	for (std::map<std::string, mesh*>::iterator itr = meshLibrary->begin(); itr != meshLibrary->end(); itr++) {
		mesh *meshToRemove = itr->second;
		delete meshToRemove;
	}

	meshLibrary->clear();

	delete meshLibrary;
}
