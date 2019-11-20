#pragma once

#include "DirectX11.h"
#include "Model.h"
#include "TextureShader.h"
#include "PlayerController.h"

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight , bool windowed);
	void Shutdown();
	bool Frame(float frameTime);
	bool LoadModel();

private:
	bool Render(float frameTime);
	bool Update(float frameTime);

private:
	DirectX11* m_D3D;
	PlayerController* m_PlayerController;
	TextureShader* m_texShader;

	Model* m_Cube;
	Model* m_Ground;
	Model* m_SkyBox;
};