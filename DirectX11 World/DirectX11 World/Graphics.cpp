#include "PCH.h"
#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = nullptr;
}

Graphics::~Graphics()
{
}

bool Graphics::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, bool windowed)
{
	//DirectX 11 Init
	m_D3D = new DirectX11();
	if (!m_D3D)
		return false;

	bool result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, !windowed, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool Graphics::LoadModels(HWND hwnd)
{
	return true;
}

void Graphics::Shutdown()
{
}

bool Graphics::Frame(float frameTime)
{
	bool result;

	//Update
	result = Update(frameTime);
	if (!result)
		return false;

	//Render
	result = Render(frameTime);
	if (!result)
		return false;

	return true;
}

bool Graphics::Update(float frameTime)
{
	//Scene Update

	return true;
}

bool Graphics::Render(float frameTime)
{
	m_D3D->BeginScene(1.0f, 1.0f, 0.7f, 1.0f);

	//Scene Render


	m_D3D->EndScene();

	return true;
}
