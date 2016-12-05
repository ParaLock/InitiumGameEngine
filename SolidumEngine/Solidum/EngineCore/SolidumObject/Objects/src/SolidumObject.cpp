#include "../include/SolidumObject.h"



SolidumObject::SolidumObject()
{
	attachedControllers = new std::list<IController*>;
}


SolidumObject::~SolidumObject()
{
	delete attachedControllers;
}


void SolidumObject::AttachController(IController * controller)
{
	attachedControllers->push_back(controller);
}

void SolidumObject::Render()
{
	if (activeShader != NULL) {
		if (activeTex != NULL) {
			activeShader->attachTex(activeTex);
		}



		activeShader->Bind();
	}

	if (activeTex != NULL) {
		activeTex->Bind();
	}

	if (activeMesh != NULL) {
		activeMesh->draw();
	}
}
