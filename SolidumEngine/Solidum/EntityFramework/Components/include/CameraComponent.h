#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "Component.h"

#include "./../../../sysInclude.h"

#include "../../../GraphicsRendering/Window/include/window.h"

#include "../../../EngineUtils/include/Timer.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../EventFramework/include/IEventListener.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../InputHandling/include/InputHandler.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataGroup.h"

#define SMOOTHING_FACTOR 100

enum CAMERA_MOVE {
	CAM_RIGHT,
	CAM_LEFT,
	CAM_UP,
	CAM_DOWN,

	CAM_FORWARD,
	CAM_BACKWARD,

	CAM_LOOK_RIGHT,
	CAM_LOOK_LEFT,
	CAM_LOOK_UP,
	CAM_LOOK_DOWN
};

class CameraComponent : public Component
{
private:

	float _movementStore[4];

	float _yaw = 0, _pitch = 0;

	float screen_width = 0, screen_height = 0;

	float _eyevec = 0.0f;

	bool _mouseLocked = false;

	Vector2i _screenCenter;

	HRTimer camTimer;

	Matrix4f _projectionMatrix, _orthoProjectionMatrix, _viewMatrix, _startViewMatrix, _worldMatrix, _matRotate, _matTranslation, _matModelMatrix;

	Vector3f _eye, _view, _up, _forward, _strafeRight;

	const Vector3f _dV, _dU;

	Vector2f _previousMousePos;

	void load() { };
	void unload() { };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

public:
	CameraComponent(float near_value, float far_value, IEntity* entity);
	~CameraComponent();

	struct InitData : public ResourceInitParams {
		InitData() {}

		
	};

	void onEvent(EVENT_PTR evt);

	void adjustYawAndPitch(float yaw, float pitch);

	void updateLook(float mouseX, float mouseY);

	void move(CAMERA_MOVE direction, float speed);

	void update(float delta);

	Matrix4f getWorldMatrix() { return _worldMatrix; };
	Matrix4f getViewMatrix() { return _viewMatrix; };
	Matrix4f getProjectionMatrix() { return _projectionMatrix; };
	Matrix4f getStartViewMatrix() { return _startViewMatrix; };
	Matrix4f getOrthoProjectionMatrix() { return _orthoProjectionMatrix; }

	Matrix4f getModelMatrix() { 

		_matTranslation = Matrix4f::get_translation(_eye);

		_matModelMatrix = _matTranslation * _matRotate;

		return _matModelMatrix; 
	}

	Vector3f getPos() { return _eye; }

	void AddRenderData(RenderDataGroup* collection);

protected:
};

#endif