#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

class Texture;
class RenderTarget;
class mesh;
class Transform;
class IShader;
class ILight;
class CameraComponent;
class MaterialPass;

class GraphicsCommand : public IResource
{
protected:
	GRAPHICS_COMMAND_TYPE _type = GRAPHICS_COMMAND_TYPE::INVALID;
private:
	uint64_t _executionThreadID;
public:
	GraphicsCommand();
	~GraphicsCommand();

	virtual GRAPHICS_COMMAND_TYPE getType() { return _type; };

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	virtual void execute() = 0;
};

