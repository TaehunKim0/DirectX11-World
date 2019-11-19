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


	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = m_rotation.y * 0.0174532925f;
	yaw = m_rotation.x * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);

	lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVector, upVector);

	return;
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

void Camera::Translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}
