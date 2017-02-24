#pragma once

#include "meshLoader.h"
#include "meshLoaderOBJ.h"
#include "../../../sysInclude.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

#include "../../GraphicsBuffers/include/GPUBuffer.h"

#include "../../../EngineUtils/include/StringManipulation.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../ActiveGraphicsAPI.h"

class meshBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	ResourceManagerPool* _managerPool;

	meshBuilder(LPCWSTR filename, ResourceManagerPool* managerPool) {
		_filename = filename;
		_managerPool = managerPool;
	}
};

class mesh : public IResource
{
private:
	IResource* _vertexBuff;
	IResource* _indexBuff;

	void generateOrthoWindowMesh(meshBuilder* builder);
public:
	mesh();
	~mesh();

	void load(IResourceBuilder *builder);
	void unload();

	int meshSize;
	int indicesSize;

	int numIndices;

	VERTEX *meshVertices;
	DWORD *meshIndices;
	
	IResource* getVertexBuff() { return _vertexBuff; }
	IResource* getIndexBuff() { return _indexBuff; }
};
