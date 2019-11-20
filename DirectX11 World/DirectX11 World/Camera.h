#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(XMFLOAT3& pos);
	void GetRotation(XMFLOAT3& rot);

	void Render();
	void GetViewMatrix(XMMATRIX& viewMatrix);

	void GenerateBaseViewMatrix();
	void GetBaseViewMatrix(XMMATRIX& viewMatrix);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix, m_baseViewMatrix;
};