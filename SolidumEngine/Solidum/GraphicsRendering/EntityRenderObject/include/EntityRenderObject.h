#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsCore/include/IGraphicsCore.h"
#include "../../RenderDataProtocal/include/RenderDataGroup.h"

#include "IEntityRenderObject.h"

#include "../../../EntityFramework/Components/include/CameraComponent.h"
#include "../../../EntityFramework/Components/include/MeshComponent.h"
#include "../../../EntityFramework/Components/include/LightComponent.h"
#include "../../../EntityFramework/Components/include/ParticleEmitterComponent.h"
#include "../../../EntityFramework/Components/include/SkydomeWeatherComponent.h"

class EntityRenderObject : public IEntityRenderObject
{
private:
	std::list<Component*> _uniqueRenderResources;
	std::map<COMPONENT_TYPE, std::map<int, Component*>> _renderResources;
public:
	EntityRenderObject();
	~EntityRenderObject();

	void addLightComponent(LightComponent* lightComponent, int index);
	void addMeshComponent(MeshComponent* meshComponent, int index);

	void setMeshTexture(Texture * tex, int index);
	void setMeshMaterial(Material* mat, int index);

	void addUniqueComponent(Component* comp);

	void attachRenderDataToGroup(RenderDataGroup* datagroup);
};

