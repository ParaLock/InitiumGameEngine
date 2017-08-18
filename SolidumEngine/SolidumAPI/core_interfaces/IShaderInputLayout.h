#pragma once

#include "../common.h"

class ShaderInputLayoutElement;

class IShaderInputLayout {
private:
public:

	virtual void generateInputLayout() = 0;

	virtual std::string getName() = 0;

	virtual std::vector<ShaderInputLayoutElement*>* getElementList() = 0;

};