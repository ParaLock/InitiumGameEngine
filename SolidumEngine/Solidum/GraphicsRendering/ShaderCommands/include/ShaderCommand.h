#pragma once
#include "../../../sysInclude.h"

#include "../../Shaders/include/IShader.h"
#include "../../Lights/include/ILight.h"
#include "../../GraphicsCommand/include/GraphicsCommand.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "../../Shaders/include/ShaderUniformGroup.h"

class MaterialPass;
class CameraComponent;
class Transform;
class mesh;
class Texture;

//DECL_GRAPHICS_COMMAND(ShaderUpdateUniformCommand,
//class DataPolicy {
//public:
//	ShaderUniformGroup _uniforms;
//
//	IShader* _shader;
//
//	struct InitData : public ResourceInitParams {
//
//		ShaderUniformGroup _uniforms;
//		IShader* _shader;
//
//		InitData() {
//
//		}
//
//		InitData(ShaderUniformGroup& uniform, IShader* shader)
//		{
//			_uniforms = uniform;
//
//			_shader = shader;
//		}
//
//
//	};
//
//}; ,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_shader = initParams->_shader;
//		dataOut->_uniforms = initParams->_uniforms;
//	}
//};,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		for each(ShaderUniformGroup::Uniform uniform in data->_uniforms.getUniforms()) {
//
//			data->_shader->updateUniform(uniform._name, uniform._data);
//		}
//	}
//};);


class ShaderUpdateUniformCommand : public GraphicsCommand<ShaderUpdateUniformCommand> {
private:
	ShaderUniformGroup _uniforms;

	IShader* _shader;
public:

	struct InitData : public ResourceInitParams {

		ShaderUniformGroup _uniforms;
		IShader* _shader;
	

		InitData() {
		
		}

		InitData(ShaderUniformGroup& uniform, IShader* shader)
		{
			_uniforms = uniform;
			_shader = shader;
		}


	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {

		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_uniforms = realBuilder->_uniforms;
		_shader = realBuilder->_shader;
	}

	void execute();
protected:
};

//DECL_GRAPHICS_COMMAND(ShaderSyncUniforms,
//class DataPolicy {
//public:
//
//	IShader* _shader;
//
//	struct InitData : public ResourceInitParams {
//
//		InitData() {
//
//		}
//
//		IShader* _shader;
//
//		InitData(IShader* shader) {
//			_shader = shader;
//		}
//	};
//
//};,
//class LoadPolicy {
//public:
//	inline static void LOAD(DataPolicy::InitData* initParams, DataPolicy* dataOut) {
//		dataOut->_shader = initParams->_shader;
//	}
//}; ,
//class ExecutePolicy {
//public:
//	inline static void EXECUTE(DataPolicy* data) {
//		data->_shader->updateGPU();
//	}
//};);

class ShaderSyncUniforms : public GraphicsCommand<ShaderSyncUniforms> {
private:
	IShader* _shader;
public:

	ShaderSyncUniforms() {};

	struct InitData : public ResourceInitParams {

		InitData() {
			
			int test = 1;
		}

		IShader* _shader;

		InitData(IShader* shader) {
			_shader = shader;
		}
	};


	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {
		InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

		_shader = realBuilder->_shader;
	}

	void execute();

protected:
};