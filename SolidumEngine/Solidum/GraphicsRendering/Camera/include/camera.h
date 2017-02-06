#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "./../../../sysInclude.h"
#include "../../Window/include/windowAccessor.h"
#include "Timer.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/IEventPublisher.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../EventFramework/include/InputEvent.h"

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define M_PI    3.14159265358979323846264338327950288

class IResourceBuilder;

class camera : public IEventListener, public IEventPublisher, public IResource
{
private:
	float heading, pitch;

	void adjustHeadingPitch(float hRad, float pRad);
	void UpdateView();

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	D3DXMATRIX matRotate, matView, matProjection, orthoMatrix, startCamView, worldMatrix;
	D3DXMATRIX transposedMatView, transposedMatProjection, transposedOrthoMatrix, transposedWorldMatrix, transposedStartCamView;

	HRTimer camTimer;

	const D3DXVECTOR3 dV, dU;
	D3DXVECTOR3 eye, view, up;

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

	void onEvent(EVENT_PTR evt);

	D3DXMATRIX& getViewMatrix() { 

		return matView;
	}
	D3DXMATRIX& getProjectionMatrix() {

		return matProjection;
	}
	D3DXMATRIX& getOrtho() { 

		return orthoMatrix;
	};
	D3DXMATRIX& getWorldMatrix() { 

		return worldMatrix;
	};

	D3DXMATRIX& getTransposedViewMatrix() {

		D3DXMatrixTranspose(&transposedMatView, &matView);

		return transposedMatView;
	}

	D3DXMATRIX& getTransposedProjectionMatrix() {

		D3DXMatrixTranspose(&transposedMatProjection, &matProjection);

		return transposedMatProjection;
	}
	D3DXMATRIX& getTransposedOrtho() {

		D3DXMatrixTranspose(&transposedOrthoMatrix, &orthoMatrix);

		return transposedOrthoMatrix;
	};
	D3DXMATRIX& getTransposedWorldMatrix() {

		D3DXMatrixTranspose(&transposedWorldMatrix, &worldMatrix);

		return transposedWorldMatrix;
	};

	D3DXVECTOR3 getView() { return view; };

	D3DXMATRIX& getStartCamView() { return startCamView; };

	D3DXMATRIX& getTransposedStartCamView() {

		D3DXMatrixTranspose(&transposedStartCamView, &startCamView);

		return transposedStartCamView;
	};

	void setPositionAndView(float x, float y, float z, float hDeg, float pDeg);

	void cameraMouseLook(unsigned long posX, unsigned long posY);

	void cameraMove(std::string direction, float speed);

	void Update();
};

#endif