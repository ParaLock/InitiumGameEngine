#pragma once
#include "../../../EventFramework/include/IEvent.h"
#include "../../../EventFramework/include/InputEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "../../../GraphicsRendering/Particles/include/Particle.h"

#include "Component.h"

class ParticleEmiterComponent
{
private:
	std::list<Particle*> _liveParticleList;
public:
	ParticleEmiterComponent();
	~ParticleEmiterComponent();
};

