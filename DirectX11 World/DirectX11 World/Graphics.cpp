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

	m_Camera = new Camera();
	m_Camera->SetPosition(0, 0, -10);
	//m_Camera->SetRotation(30, 0, 0);

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
	m_Camera->Translate(0, 0.001, 0);



	return true;
}

bool Graphics::Render(float frameTime)
{
	XMMATRIX viewMatrix, worldMatrix , projectionMatrix;
	bool result;

	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	m_D3D->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);

	model->Render(frameTime);
	m_texShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTexture()->GetTextureView());

	m_D3D->EndScene();

	return true;
}
