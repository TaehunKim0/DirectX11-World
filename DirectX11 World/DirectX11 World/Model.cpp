#include "PCH.h"
#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext, const WCHAR* modelFileName, const WCHAR* textureFileName)
{
	bool result;

	m_D3DDevice = device;
	m_D3DDeviceContext = deviceContext;

	result = LoadModel(modelFileName);
	if (!result)
		return false;

	result = InitializeBuffers();
	if (!result)
		return false;

	result = LoadTexture(textureFileName);
	if (!result)
		return false;

	return true;
}

void Model::Update(float frameTime)
{
}

void Model::Render(float frameTime)
{
	RenderBuffers(frameTime);
}

void Model::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
	ReleaseModel();
}

bool Model::InitializeBuffers()
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	vertices = new VertexType[m_VertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[m_IndexCount];
	if (!indices)
		return false;

	//Vertex
	for (i = 0; i < m_VertexCount; i++)
	{	
		vertices[i].position = XMFLOAT3(m_Model[i].x, m_Model[i].y, m_Model[i].z);
		vertices[i].texture = XMFLOAT2(m_Model[i].tu, m_Model[i].tv);
		vertices[i].normal = XMFLOAT3(m_Model[i].nx, m_Model[i].ny, m_Model[i].nz);

		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;


	result = m_D3DDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
	if (FAILED(result))
		return false;


	//Index
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;


	result = m_D3DDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	return true;
}

void Model::ShutdownBuffers()
{
	if (m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = 0;
	}

	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = 0;
	}
}

bool Model::LoadModel(const WCHAR* modelFileName)
{
	std::ifstream fin;
	char input;
	int i;

	fin.open(modelFileName);

	if (fin.fail())
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin >> m_VertexCount;

	m_IndexCount = m_VertexCount;

	m_Model = new ModelType[m_VertexCount];
	if (!m_Model)
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	for (i = 0; i < m_VertexCount; i++)
	{
		fin >> m_Model[i].x >> m_Model[i].y >> m_Model[i].z;
		fin >> m_Model[i].tu >> m_Model[i].tv;
		fin >> m_Model[i].nx >> m_Model[i].ny >> m_Model[i].nz;
	}

	fin.close();

	return true;
}

void Model::ReleaseModel()
{
	if (m_Model)
	{
		delete[] m_Model;
		m_Model = 0;
	}
}

bool Model::LoadTexture(const WCHAR* textureFileName)
{
	bool result;

	m_Texture = new Texture;
	if (!m_Texture)
	{
		return false;
	}

	result = m_Texture->Initialize(m_D3DDevice, m_D3DDeviceContext, textureFileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void Model::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		SAFE_DELETE(m_Texture);
	}
}

void Model::RenderBuffers(float frameTime)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	m_D3DDeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	m_D3DDeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_D3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
