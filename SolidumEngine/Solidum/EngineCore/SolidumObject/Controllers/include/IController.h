#pragma once

#include "../../../../sysInclude.h"

enum CONTROLLER_MESSAGE {
	//MOVE CONTROLLER
	MOVE_FORWARD = 0x1,
	MOVE_BACKWARD = 0x2,
	MOVE_LEFT = 0x3,
	MOVE_RIGHT = 0x4,
	MOVE_UP = 0x5,
	MOVE_DOWN = 0x6
};

struct ControllerPacket {
	CONTROLLER_MESSAGE msg;
	std::vector<void*> dataElements;
};

class SolidumObject;

class IController
{
public:
	IController();
	~IController();

	SolidumObject* activeParent = NULL;

	virtual void execute(CONTROLLER_MESSAGE msg) = 0;
};

