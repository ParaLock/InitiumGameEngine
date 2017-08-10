#pragma once

#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

class Texture;
class RenderTarget;
class mesh;
class Transform;
class IShader;
class ILight;
class CameraComponent;
class MaterialPass;

class IGraphicsCommand {
public:

	virtual void execute() = 0;

private:
};

//template<typename LOAD_POLICY, typename EXECUTE_POLICY, typename DATA_POLICY>
//class GraphicsCommand : public IGraphicsCommand, public Resource<GraphicsCommand<LOAD_POLICY, EXECUTE_POLICY, DATA_POLICY>,
//	GenericFactory, ResourcePool>
//{
//protected:
//private:
//public:
//	GraphicsCommand() {};
//	~GraphicsCommand() {};
//
//	DATA_POLICY _data;
//
//	typedef typename DATA_POLICY::InitData InitData;
//
//	void unload() {};
//	void release() { this->release(); }
//
//	virtual void load() { 
//
//		LOAD_POLICY::LOAD(dynamic_cast<InitData>(getContext()->getResourceInitParams()), &_data); 
//	
//		int test = 1;
//
//	}
//	virtual void execute() { EXECUTE_POLICY::EXECUTE(&_data); };
//};
//
//#define DECL_GRAPHICS_COMMAND(CMD_NAME, DATA_POLICY, LOAD_POLICY, EXECUTE_POLICY)\
//namespace CMD_NAME##_policy{\
//DATA_POLICY\
//\
// LOAD_POLICY\
//\
// EXECUTE_POLICY\
//}\
//typedef GraphicsCommand<CMD_NAME##_policy::LoadPolicy, CMD_NAME##_policy::ExecutePolicy, CMD_NAME##_policy::DataPolicy> CMD_NAME;

template<typename T_CMD>
class GraphicsCommand : public IGraphicsCommand, public Resource<T_CMD, GenericFactory, ResourcePool>{
public:
	virtual void load() = 0;
	virtual void unload() {}
	virtual void execute() = 0;
private:
};
