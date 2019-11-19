#include "PCH.h"
#include "Texture.h"
	

Texture::Texture()
{
	m_Texture = nullptr;
	m_TextureView = nullptr;
}


Texture::~Texture()
{
}

bool Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName)
{
	int height, width;

	//LoadTargar로 m_Target 배열에 targa 파일을 로드
	bool result = LoadTarga(fileName, height, width); //targa 이미지는 디폴트로 뒤집어져 있어서 이미지를 반전해야 합니다.
	if (!result)
		return false;

	//targa 데이터를 로드할 DirectX 텍스쳐 정보 구조체를 설정해야 합니다. 
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	//구조체를 다 채웠으면 CreateTexture2D를 호출해 빈 텍스쳐를 만들고, targa 데이터를 빈 텍스쳐에 복사합니다.
	HRESULT hResult = device->CreateTexture2D(&textureDesc, NULL, &m_Texture);
	if (FAILED(hResult))
	{
		return false;
	}

	unsigned int rowPitch = (width * 4) * sizeof(unsigned char);
	deviceContext->UpdateSubresource(m_Texture, 0, NULL, m_TargaData, rowPitch, 0); //빈 텍스쳐에 복사

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	//중요한 두 개의 MipMap 변수들을 설정하는데, 어떤 거리에서도 높은 품질의 텍스쳐 렌더링을 할 수 있게
	//모든 범위의 MipMap 레벨을 가질 수 있게 합니다
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	//텍스쳐가 로딩된 다음 셰이더 리소스 뷰를 생성해서 셰이더 안에 텍스쳐를 세팅할 수 있는 포인터를 가집니다
	hResult = device->CreateShaderResourceView(m_Texture, &srvDesc, &m_TextureView);
	if (FAILED(hResult))
	{
		return false;
	}

	deviceContext->GenerateMips(m_TextureView);

	delete[] m_TargaData;
	m_TargaData = nullptr;

	return true;
}

bool Texture::LoadTarga(const WCHAR* fileName, int& height, int& width)
{
	//32 bit targa 파일만 가능한 코드
	FILE* filePtr;

	_bstr_t b(fileName);
	const char* FileName = b;

	int error = fopen_s(&filePtr, FileName, "rb");
	if (error != 0)
	{
		return false;
	}

	TargaHeader targaFileHeader;
	unsigned int count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	int bpp = (int)targaFileHeader.bpp;

	if (bpp != 32)
	{
		return false;
	}

	int imageSize = width * height * 4;

	unsigned char* targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	m_TargaData = new unsigned char[imageSize];
	if (!m_TargaData)
	{
		return false;
	}

	int index = 0;

	int k = (width * height * 4) - (width * 4);

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			m_TargaData[index + 0] = targaImage[k + 2];  // Red.
			m_TargaData[index + 1] = targaImage[k + 1];  // Green.
			m_TargaData[index + 2] = targaImage[k + 0];  // Blue
			m_TargaData[index + 3] = targaImage[k + 3];  // Alpha

			k += 4;
			index += 4;
		}

		k -= (width * 8);
	}

	delete[] targaImage;
	targaImage = 0;

	return true;
}

void Texture::Shutdown()
{
	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = 0;
	}

	if (m_TextureView)
	{
		m_TextureView->Release();
		m_TextureView = 0;
	}
}

ID3D11ShaderResourceView* Texture::GetTextureView()
{
	return m_TextureView;
}