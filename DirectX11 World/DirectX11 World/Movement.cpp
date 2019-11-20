#include "PCH.h"
#include "Movement.h"


Movement::Movement()
{
	m_Position = XMFLOAT3();
	m_Rotation = XMFLOAT3();

	m_FrameTime = 0.0f;

	m_ForwardSpeed = 0.0f;
	m_BackwardSpeed = 0.0f;
	m_LeftSpeed = 0.0f;
	m_RightSpeed = 0.0f;
	m_UpwardSpeed = 0.0f;
	m_DownwardSpeed = 0.0f;
	m_LeftTurnSpeed = 0.0f;
	m_RightTurnSpeed = 0.0f;
	m_LookUpSpeed = 0.0f;
	m_LookDownSpeed = 0.0f;

	m_MoveSpeed = 0.5f;
}


Movement::~Movement()
{
}


void Movement::SetPosition(float x, float y, float z)
{
	m_Position = XMFLOAT3(x, y, z);
	return;
}


void Movement::SetRotation(float x, float y, float z)
{
	m_Rotation = XMFLOAT3(x, y, z);
	return;
}

void Movement::SetMoveSpeed(bool keydown, float moveSpeed) 
{
	if (keydown)
	{
		m_MoveSpeed = moveSpeed;
	}
	else
	{
		m_MoveSpeed = 0.5f;
	}

	return;
}

void Movement::GetPosition(XMFLOAT3& pos)
{
	pos = m_Position;
	return;
}


void Movement::GetRotation(XMFLOAT3& rot)
{
	rot = m_Rotation;
	return;
}


void Movement::SetFrameTime(float time)
{
	m_FrameTime = time;
	return;
}


void Movement::MoveForward(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_ForwardSpeed += m_FrameTime * 0.001f;

		if (m_ForwardSpeed > (m_FrameTime * 0.03f))
		{
			m_ForwardSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_ForwardSpeed -= m_FrameTime * 0.0007f;

		if (m_ForwardSpeed < 0.0f)
		{
			m_ForwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_Rotation.y * 0.0174532925f;

	// Update the position.
	m_Position.x += sinf(radians) * (m_ForwardSpeed * m_MoveSpeed);
	m_Position.z += cosf(radians) * (m_ForwardSpeed * m_MoveSpeed);

	return;
}


void Movement::MoveBackward(bool keydown)
{
	float radians;


	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_BackwardSpeed += m_FrameTime * 0.001f;

		if (m_BackwardSpeed > (m_FrameTime * 0.03f))
		{
			m_BackwardSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_BackwardSpeed -= m_FrameTime * 0.0007f;

		if (m_BackwardSpeed < 0.0f)
		{
			m_BackwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_Rotation.y * 0.0174532925f;

	// Update the position.
	m_Position.x -= sinf(radians) * (m_BackwardSpeed * m_MoveSpeed);
	m_Position.z -= cosf(radians) * (m_BackwardSpeed * m_MoveSpeed);

	return;
}

void Movement::MoveLeft(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_LeftSpeed += m_FrameTime * 0.001f;
		
		if (m_LeftSpeed > (m_FrameTime * 0.03f))
		{
			m_LeftSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_LeftSpeed -= m_FrameTime * 0.0007f;

		if (m_LeftSpeed < 0.0f)
		{
			m_LeftSpeed = 0.0f;
		}
	}

	radians = (m_Rotation.y - 90) * 0.0174532925f; //Rotates movement 90 degrees so its left and right instead of forward and backward.

	m_Position.x += sinf(radians) * (m_LeftSpeed * m_MoveSpeed);
	m_Position.z += cosf(radians) * (m_LeftSpeed * m_MoveSpeed);


	return;
}

void Movement::MoveRight(bool keydown)
{
	float radians;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_RightSpeed += m_FrameTime * 0.001f;

		if (m_RightSpeed > (m_FrameTime * 0.03f))
		{
			m_RightSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_RightSpeed -= m_FrameTime * 0.0007f;

		if (m_RightSpeed < 0.0f)
		{
			m_RightSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = (m_Rotation.y - 90) * 0.0174532925f; //Rotates movement 90 degrees so its left and right instead of forward and backward.

												  // Update the position.
	m_Position.x -= sinf(radians) * (m_RightSpeed * m_MoveSpeed);
	m_Position.z -= cosf(radians) * (m_RightSpeed * m_MoveSpeed);

	return;
}

void Movement::MoveUpward(bool keydown)
{
	if (keydown)
	{
		m_UpwardSpeed += m_FrameTime * 0.003f;

		if (m_UpwardSpeed > (m_FrameTime * 0.03f))
		{
			m_UpwardSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_UpwardSpeed -= m_FrameTime * 0.002f;

		if (m_UpwardSpeed < 0.0f)
		{
			m_UpwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_Position.y += (m_UpwardSpeed * m_MoveSpeed);

	return;
}


void Movement::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_DownwardSpeed += m_FrameTime * 0.003f;

		if (m_DownwardSpeed > (m_FrameTime * 0.03f))
		{
			m_DownwardSpeed = m_FrameTime * 0.03f;
		}
	}
	else
	{
		m_DownwardSpeed -= m_FrameTime * 0.002f;

		if (m_DownwardSpeed < 0.0f)
		{
			m_DownwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_Position.y -= (m_DownwardSpeed * m_MoveSpeed);

	return;
}

void Movement::MoveMouse(int mouseChangeX, int mouseChangeY, float mouseSensitivity)//When the method is ran these variables must be passed to the method.
{
	m_Rotation.y += mouseChangeX * mouseSensitivity;//Set rotationX to rotationX + mouse change on the y axis.

	if ((m_Rotation.x + (mouseChangeY * mouseSensitivity)) < 90 && (m_Rotation.x + (mouseChangeY * mouseSensitivity)) > -90)//Check that any added rotation doesnt exceed the boundries for X rotation.
	{
		m_Rotation.x += mouseChangeY * mouseSensitivity;//Set rotationX to rotationX + mouse change on the y axis, the smaller the mouse sensitivity the more it reduces the rotation.
	}
}
