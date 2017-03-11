#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

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

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	virtual void addInput(int type, std::string name, UINT index, BYTE mask) = 0;

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void generateInputLayout() = 0;

	std::string getName() { return _name; };

	UINT getDataStride() {return _dataStride; };
};

