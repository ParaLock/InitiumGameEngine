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
	INPUT_LAYOUT_ELEMENT_CLASS _class = INPUT_LAYOUT_ELEMENT_CLASS::PER_VERTEX_DATA;
	BYTE _mask;

	int _type;
};

class ShaderInputLayout : public IResource
{
protected:
	std::vector<ShaderInputLayoutElement*> *_inputLayoutElementList;

	std::string _name;

	UINT _dataStride = 0;
public:
	ShaderInputLayout();
	~ShaderInputLayout();

	struct InitData : public IResourceBuilder {
		InitData() {

		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	virtual void addInput(int type, std::string name, UINT index, BYTE mask) = 0;

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void generateInputLayout() = 0;

	std::string getName() { return _name; };

	std::vector<ShaderInputLayoutElement*>* getElementList() { return _inputLayoutElementList; }

	UINT getDataStride() {return _dataStride; };
};

