#pragma once
#include "../../../sysInclude.h"

class Texture;
class Material;

class RenderDataGroup;
class RenderDataPacket;
class LightComponent;
class MeshComponent;
class Component;

class IEntityRenderObject
{
public:
	IEntityRenderObject() {};
	~IEntityRenderObject() {};

	virtual void addLightComponent(LightComponent* lightComponent, int index) = 0;
	virtual void addMeshComponent(MeshComponent* meshComponent, int index) = 0;

	virtual void setMeshTexture(Texture * tex, int index) = 0;
	virtual void setMeshMaterial(Material* mat, int index) = 0;

	virtual void addUniqueComponent(Component* comp) = 0;

	virtual void attachRenderDataToGroup(RenderDataGroup* datagroup) = 0;
};

