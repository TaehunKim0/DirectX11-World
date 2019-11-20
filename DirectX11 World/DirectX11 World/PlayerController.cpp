#include "PCH.h"
#include "PlayerController.h"
using namespace std;

PlayerController::PlayerController()
{
	m_Camera = 0;
	m_Input = 0;
	m_Timer = 0;
	m_Movement = 0;
}

PlayerController::~PlayerController()
{

}

bool PlayerController::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	LightMovement = false;
	SmoothShadows = true;
	ShowShadowmap = false;
	Rotate = false;

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	m_Input = new Input;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player input object.", L"Error", MB_OK);
		return false;
	}

	CurrentInteraction = false;

	// Create the timer object.
	m_Timer = new Timer;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create movement object.
	m_Movement = new Movement;
	if (!m_Movement)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Movement->SetPosition(0.0f, 0.0f, -10.0f);
	m_Movement->SetRotation(0.0f, 0.0f, 0.0f);

	// Create variables for viewing position of the scene.
	XMFLOAT3 movPosition, movRotation;
	m_Movement->GetPosition(movPosition);
	m_Camera->SetPosition(movPosition.x, movPosition.y, movPosition.z);
	m_Movement->GetRotation(movRotation);
	m_Camera->SetRotation(movRotation.x, movRotation.y, movRotation.z);
	m_Camera->GenerateBaseViewMatrix();

	return true;
}

// Called every frame.
bool PlayerController::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovement(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool PlayerController::HandleMovement(float frameTime)
{
	unsigned char key;
	bool keyDown, keyPressed;
	XMFLOAT3 rot, pos;
	int mouseChangeX, mouseChangeY;
	float mouseSensitivity = 0.1f;// Used to affect mouseMovement speed easily.

	// Gets the mouseChange between frames for the X axis.
	mouseChangeX = m_Input->GetMouseXChange();

	// Gets the mouseChange between frames for the Y axis.
	mouseChangeY = m_Input->GetMouseYChange();

	// Set the frame time for calculating the updated position.
	m_Movement->SetFrameTime(frameTime);

	// Handle the input.
	key = DIK_W;
	keyDown = m_Input->IsKeyDown(DIK_W);
	m_Movement->MoveForward(keyDown);

	key = DIK_S;
	keyDown = m_Input->IsKeyDown(key);
	m_Movement->MoveBackward(keyDown);

	key = DIK_A;
	keyDown = m_Input->IsKeyDown(key);
	m_Movement->MoveLeft(keyDown);

	key = DIK_D;
	keyDown = m_Input->IsKeyDown(key);
	m_Movement->MoveRight(keyDown);

	key = DIK_SPACE;
	keyDown = m_Input->IsKeyDown(key);
	m_Movement->MoveUpward(keyDown);

	key = DIK_LCONTROL;
	keyDown = m_Input->IsKeyDown(key);
	m_Movement->MoveDownward(keyDown);

	// Run the position method moveMouse and pass in variables from the input class.
	m_Movement->MoveMouse(mouseChangeX, mouseChangeY, mouseSensitivity);

	// Get the new view point position/rotation.
	m_Movement->GetPosition(pos);
	m_Movement->GetRotation(rot);

	// Reset the cursor to the centre of the screen as we now have mouse movement.
	m_Input->ResetMousePosition();

	// Set the position of the camera.
	m_Camera->SetPosition(pos.x, pos.y, pos.z);
	m_Camera->SetRotation(rot.x, rot.y, rot.z);

	return true;
}

bool PlayerController::Render()
{
	m_Camera->Render();

	return true;
}

void PlayerController::GetCameraViewMatrix(XMMATRIX& matrix)
{
	m_Camera->GetViewMatrix(matrix);
	return;
}

void PlayerController::GetBaseCameraViewMatrix(XMMATRIX& matrix)
{
	m_Camera->GetBaseViewMatrix(matrix);
	return;
}

void PlayerController::GetPlayerPosition(XMFLOAT3& pos)
{
	m_Movement->GetPosition(pos);

	return;
}

void PlayerController::Shutdown()
{
	if (m_Camera)
	{
		SAFE_DELETE(m_Camera);
	}

	if (m_Input)
	{
		m_Input->Shutdown();
		SAFE_DELETE(m_Input);
	}

	if (m_Timer)
	{
		SAFE_DELETE(m_Timer);
	}

	if (m_Movement)
	{
		SAFE_DELETE(m_Movement);
	}
}

