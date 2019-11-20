#pragma once
class Movement
{
public:
	Movement();
	~Movement();

	void SetPosition(float x, float y , float z);
	void SetRotation(float x , float y , float z);
	void SetMoveSpeed(bool keydown, float moveSpeed);

	void GetPosition(XMFLOAT3& pos);
	void GetRotation(XMFLOAT3& rot);

	void SetFrameTime(float time);

	void MoveForward(bool keydown);
	void MoveBackward(bool keydown);
	void MoveLeft(bool keydown);
	void MoveRight(bool keydown);
	void MoveUpward(bool keydown);
	void MoveDownward(bool keydown);
	void MoveMouse(int mouseChangeX, int mouseChangeY, float mouseSensitivity);


private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;

	float m_FrameTime;

	float m_ForwardSpeed, m_BackwardSpeed;
	float m_LeftSpeed, m_RightSpeed;
	float m_UpwardSpeed, m_DownwardSpeed;
	float m_LeftTurnSpeed, m_RightTurnSpeed;
	float m_LookUpSpeed, m_LookDownSpeed;

	float m_MoveSpeed;
};
