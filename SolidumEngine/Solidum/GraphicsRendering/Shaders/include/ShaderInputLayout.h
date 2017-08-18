#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../../SolidumAPI/core_interfaces/IShaderInputLayout.h"

#include "../../../../SolidumAPI/core_objects/include/ShaderInputLayoutElement.h"

class GenericFactory;

class ResourcePool;

class ShaderInputLayout : public Resource<ShaderInputLayout, GenericFactory, ResourcePool>, public IShaderInputLayout
{

public:
	ShaderInputLayout();
	~ShaderInputLayout();

	struct InitData : public ResourceInitParams {
		InitData() {

		}

		
	};

	void load() { };
	void unload() { };

	virtual void addInput(int type, std::string name, UINT index, BYTE mask) = 0;

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void generateInputLayout() = 0;

	std::string getName() { return _name; };

	std::vector<ShaderInputLayoutElement*>* getElementList() { return _inputLayoutElementList; }

	UINT getDataStride() {return _dataStride; };

protected:
	std::vector<ShaderInputLayoutElement*> *_inputLayoutElementList;

	std::string _name;

	UINT _dataStride = 0;
};

