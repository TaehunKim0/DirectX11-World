#pragma once

#include "DDSTextureLoader.h"
class Texture
{
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	Texture();
	~Texture();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName);
	bool DDSInitialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName);
	void Shutdown();

	ID3D11ShaderResourceView* GetTextureView();

private:
	bool LoadTarga(const WCHAR* fileName, int& height, int& width);

private:
	ID3D11ShaderResourceView* m_TextureView;
	unsigned char* m_TargaData;
	ID3D11Texture2D* m_Texture;
};

