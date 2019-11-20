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

	m_texShader = new TextureShader();
	result = m_texShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
		return false;

	m_PlayerController = new PlayerController;

	result = m_PlayerController->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
		return false;

	LoadModel();

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

bool Graphics::LoadModel()
{
	bool result;

	m_Cube = new Model();
	result = m_Cube->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), L"data/cube.txt", L"data/stone01.tga");
	if (!result)
		return false;

	m_Ground = new Model();
	result = m_Ground->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), L"data/cube.txt", L"data/grass2.tga");
	if (!result)
		return false;

	m_Ground->SetPosition(0.0f, -1.5f, 0.0f);

	m_SkyBox = new Model();
	result = m_SkyBox->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), L"data/Sphere.txt", L"data/Skybox.tga");
	if (!result)
		return false;
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
	XMMATRIX viewMatrix, worldMatrix , projectionMatrix, OrginWorldMatrix;
	bool result;
	XMFLOAT3 pos;

	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetWorldMatrix(OrginWorldMatrix);

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_PlayerController->GetCameraViewMatrix(viewMatrix);
	m_PlayerController->GetPlayerPosition(pos);


	/*Cube Render*/
	m_Cube->Render(frameTime);
	m_texShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Cube->GetTexture()->GetTextureView());

	/*Ground Render*/
	m_Ground->GetPosition(pos);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(5.0f, 0.2f, 5.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	m_Ground->Render(frameTime);
	m_texShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Ground->GetTexture()->GetTextureView());

	/*SkyBox Render*/
	m_PlayerController->GetPlayerPosition(pos);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(-10.0f, -100.0f, -10.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	m_SkyBox->Render(frameTime);
	m_texShader->Render(m_D3D->GetDeviceContext(), m_SkyBox->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_SkyBox->GetTexture()->GetTextureView());


	m_D3D->EndScene();

	return true;
}
