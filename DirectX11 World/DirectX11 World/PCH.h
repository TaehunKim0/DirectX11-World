#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

template<class T>
void const SAFE_DELETE(T* x) { delete x; x = nullptr; }

template<class T>
void const SAFE_RELEASE(T* x) { x->Release(); x = nullptr; }

#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
using namespace DirectX;