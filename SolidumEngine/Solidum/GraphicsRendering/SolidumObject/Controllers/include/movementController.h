#pragma once

#include "IController.h"

class movementController : public IController
{
public:
	movementController(SolidumObject* parent);
	~movementController();

	void execute(ControllerPacket* pckt);
};

