#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "./../../../sysInclude.h"
#include "../../Window/include/windowAccessor.h"
#include "Timer.h"

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define M_PI    3.14159265358979323846264338327950288

class camera
{
private:
	float heading, pitch;

	void adjustHeadingPitch(float hRad, float pRad);
	void UpdateView();

	D3DXMATRIX matRotate, matView, matProjection, orthoMatrix, startCamView;

	HRTimer camTimer;

	const D3DXVECTOR3 dV, dU;
	D3DXVECTOR3 eye, view, up;

	D3DXMATRIX worldMatrix;

	D3DXVECTOR3 forward, strafeRight;
	float movementToggles[4];

	POINT mousePos;

	float mouseOldPosX;
	float mouseOldPosY;
	float mouseMoveDiff;

	void setCamStartView();

public:
	camera(float near_value, float far_value);

	~camera();

	bool lockMouse;

	D3DXMATRIX& getViewMatrix() { return matView; }
	D3DXMATRIX& getProjectionMatrix() { return matProjection; }
	D3DXMATRIX& getOrtho() { return orthoMatrix; };
	D3DXMATRIX& getWorldMatrix() { return worldMatrix; };
	D3DXVECTOR3 getView() { return view; };

	D3DXMATRIX& getStartCamView() { return startCamView; };

	void setPositionAndView(float x, float y, float z, float hDeg, float pDeg);

	void cameraMouseLook();

	void cameraMove(std::string direction, float speed);

	void Update();
};

#endif