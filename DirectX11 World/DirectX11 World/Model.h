#pragma once

#include "GameObject.h"
#include "Texture.h"

struct VertexType
{
	XMFLOAT3  position;
	XMFLOAT2  texture;
	XMFLOAT3  normal;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

struct ConstantBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};

class Model : public GameObject
{
public:
	Model();
	~Model();

public:
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* modelFileName, const WCHAR* textureFileName);
	virtual void Update(float frameTime);
	virtual void Render(float frameTime);

	void Shutdown();


private:
	bool InitializeBuffers();
	void ShutdownBuffers();

	bool LoadModel(const WCHAR* modelFileName);
	void ReleaseModel();

	bool LoadTexture(const WCHAR* textureFileName);
	void ReleaseTexture();

	void RenderBuffers(float frameTime);

private:
	ID3D11Device* m_D3DDevice;
	ID3D11DeviceContext* m_D3DDeviceContext;

	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	ID3D11Buffer* m_ConstantBuffer;

	ID3D11RasterizerState* m_WireFrame;

	UINT m_VertexCount;
	UINT m_IndexCount;

	ModelType* m_Model;
	Texture* m_Texture;

public:
	UINT GetIndexCount() {
		return m_IndexCount;
	}
	Texture* GetTexture() {
		return m_Texture;
	}
};