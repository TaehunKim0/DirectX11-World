#pragma once

#include "DirectX11.h"

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight , bool windowed);
	bool LoadModels(HWND hwnd);
	void Shutdown();
	bool Frame(float frameTime);

private:
	bool Render(float frameTime);
	bool Update(float frameTime);

private:
	DirectX11* m_D3D;
};