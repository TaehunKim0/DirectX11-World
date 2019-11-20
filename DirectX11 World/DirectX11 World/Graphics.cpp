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

	model = new Model();
	result = model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), L"data/cube.txt", L"data/stone01.tga");
	if (!result)
		return false;

	m_texShader = new TextureShader();
	result = m_texShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
		return false;

	m_PlayerController = new PlayerController;

	result = m_PlayerController->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
		return false;

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
	bool result;

	m_PlayerController->Frame();

	/*if (m_PlayerController->LightMovement)
	{
		result = HandleLightMovement(frameTime);
		if (!result)
		{
			return false;
		}
	}*/

	// If rotation trigger is enabled then increment the roation.
	//if (m_PlayerController->Rotate)
	//{
	//	cubeRotation += 0.01f;
	//}


	return true;
}

bool Graphics::Render(float frameTime)
{
	XMMATRIX viewMatrix, worldMatrix , projectionMatrix;
	bool result;
	XMFLOAT3 pos;

	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_PlayerController->GetCameraViewMatrix(viewMatrix);
	m_PlayerController->GetPlayerPosition(pos);

	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(-10.0f, 10.0f, 10.0f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	model->Render(frameTime);
	m_texShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, model->GetTexture()->GetTextureView());

	m_D3D->EndScene();

	return true;
}
