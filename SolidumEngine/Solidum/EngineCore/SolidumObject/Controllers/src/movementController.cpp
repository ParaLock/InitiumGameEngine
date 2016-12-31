#include "../include/movementController.h"


movementController::movementController(SolidumObject* parent)
{
	activeParent = parent;
}


movementController::~movementController()
{
}

void movementController::execute(ControllerPacket* pckt)
{
	D3DXVECTOR3 *pos;
	D3DXMATRIX *objMatrix;

	float *speed;

	switch(pckt->msg) {
	case MOVE_LEFT:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->x = pos->x - *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	case MOVE_RIGHT:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->x = pos->x + *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	case MOVE_FORWARD:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->z = pos->z + *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	case MOVE_BACKWARD:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->z = pos->z - *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	case MOVE_UP:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->y = pos->y + *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	case MOVE_DOWN:
		pos = (D3DXVECTOR3*)pckt->dataElements[0];
		objMatrix = (D3DXMATRIX*)pckt->dataElements[1];
		speed = (float*)pckt->dataElements[2];

		pos->y = pos->y - *speed;

		D3DXMatrixTranslation(objMatrix, pos->x, pos->y, pos->z);
		break;
	default:
		break;
	}
}
