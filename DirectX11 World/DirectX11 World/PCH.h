#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <iostream>
#include <comdef.h>
#include <fstream>
#include <memory>
#include <d3dcompiler.h>

using namespace DirectX;
using namespace Microsoft::WRL;

#include "TypeDef.h"