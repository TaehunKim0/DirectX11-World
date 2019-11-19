#pragma once
class GameObject
{
protected:
	XMMATRIX m_World;
	XMMATRIX m_View;
	XMMATRIX m_Projection;

public:
	virtual void Update(float frameTime) = 0;
	virtual void Render(float frameTime) = 0;

};