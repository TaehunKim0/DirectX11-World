#include "PCH.h"
#include "Camera.h"

Camera::Camera()
{
	m_position = XMFLOAT3();
	m_rotation = XMFLOAT3();
}

Camera::~Camera()
{
}


void Camera::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	m_rotation = XMFLOAT3(x, y, z);
	return;
}

void Camera::GetPosition(XMFLOAT3& pos)
{
	pos = m_position;
	return;
}

void Camera::GetRotation(XMFLOAT3& rot)
{
	m_rotation = rot;
	return;
}


void Camera::Render()
{
	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.y * 0.0174532925f;
	yaw = m_rotation.x * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);


	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	//D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);


	// Translate the rotated camera position to the location of the viewer.
	//lookAt = position + lookAt;
	lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	//D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVector, upVector);
}


void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void Camera::GenerateBaseViewMatrix()
{
	XMFLOAT3 up, position, lookAt;
	float radians;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;

	radians = m_rotation.y * 0.0174532925f;

	lookAt.x = sinf(radians) + m_position.x;
	lookAt.y = m_position.y;
	lookAt.z = cosf(radians) + m_position.z;

	m_baseViewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up));
	return;
}


void Camera::GetBaseViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_baseViewMatrix;
	return;
}