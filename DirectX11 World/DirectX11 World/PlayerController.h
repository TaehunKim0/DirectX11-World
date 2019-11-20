#pragma once

#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "Movement.h"

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	bool Initialize(HINSTANCE, HWND, int, int);
	bool Frame();
	bool HandleMovement(float);
	bool Render();

	void GetCameraViewMatrix(XMMATRIX&);
	void GetBaseCameraViewMatrix(XMMATRIX&);
	void GetPlayerPosition(XMFLOAT3&);

	void Shutdown();

private:
	Camera* m_Camera;
	Input* m_Input;
	Timer* m_Timer;
	Movement* m_Movement;

	bool CurrentInteraction;

public:
	bool LightMovement;
	bool SmoothShadows;
	bool ShowShadowmap;
	bool Rotate;
};

