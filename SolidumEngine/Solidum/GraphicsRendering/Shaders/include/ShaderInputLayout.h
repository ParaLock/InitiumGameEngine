#pragma once
#include "../../../sysInclude.h"

class ShaderInputLayout
{
protected:
	std::list<std::pair<std::string, std::string>> *_inputLayoutElementList;

	std::string _name;

	UINT _dataStride = 0;
public:
	ShaderInputLayout();
	~ShaderInputLayout();

	void addInput(std::string type, std::string name);

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);

	virtual void generateInputLayout();

	std::string getName() { return _name; };

	UINT getDataStride() { return _dataStride; };
};

