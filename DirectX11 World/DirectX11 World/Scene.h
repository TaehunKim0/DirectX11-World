#pragma once
class Scene
{
private:


public:
	virtual void OnEnter();
	virtual void OnExit();

	virtual void Update(float frameTime);
	virtual void Render(float frameTime);
};