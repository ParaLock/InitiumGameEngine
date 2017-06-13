#pragma once
#include "../../../sysInclude.h"

class ShaderUniformGroup
{
private:
	std::map<std::string, std::shared_ptr<void>> _uniforms;
public:
	ShaderUniformGroup();
	~ShaderUniformGroup();

	template<typename T>
	void addUniform(T data, std::string name) {

		T* sData = new T;

		*sData = data;

		std::shared_ptr<void> sDataPtr = std::shared_ptr<void>(sData);

		_uniforms.insert({name, sDataPtr });
	}

	std::shared_ptr<void> getUniform(std::string name) {
		return _uniforms.at(name);
	}

	std::map<std::string, std::shared_ptr<void>>& getUniformsMap() { return _uniforms; }
};

