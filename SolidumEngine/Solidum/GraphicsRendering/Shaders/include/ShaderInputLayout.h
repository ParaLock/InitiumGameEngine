#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceManagement/include/IResource.h"

class ShaderInputLayoutElement {
public:
	ShaderInputLayoutElement(std::string semantic, int type, UINT index, BYTE mask) {
		_semantic = semantic;
		_type = type;
		_index = index;
		_mask = mask;
	}

	UINT _index;
	std::string _semantic;

	BYTE _mask;

	int _type;
};

class ShaderInputLayout : public IResource
{
protected:
	std::list<ShaderInputLayoutElement*> *_inputLayoutElementList;

	std::string _name;

	UINT _dataStride = 0;
public:
	ShaderInputLayout();
	~ShaderInputLayout();

	virtual void addInput(int type, std::string name, UINT index, BYTE mask);

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);
	virtual void generateInputLayout();

	std::string getName() { return _name; };

	UINT getDataStride() { return _dataStride; };
};

