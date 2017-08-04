#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

class GenericFactory;

class ShaderInputLayoutElement {
public:
	ShaderInputLayoutElement(std::string semantic, int type, UINT index, BYTE mask, bool hardCodedIndex) {
		_semantic = semantic;
		_type = type;
		_index = index;
		_mask = mask;
		_hardCodedIndex = hardCodedIndex;
	}

	bool _hardCodedIndex;

	UINT _index;
	std::string _semantic;
	INPUT_LAYOUT_ELEMENT_CLASS _class = INPUT_LAYOUT_ELEMENT_CLASS::PER_VERTEX_DATA;
	BYTE _mask;

	int _type;
};

class ResourcePool;

class ShaderInputLayout : public Resource<ShaderInputLayout, GenericFactory, ResourcePool>
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

