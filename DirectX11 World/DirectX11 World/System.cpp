#include "PCH.h"
#include "System.h"

System::System()
	: m_Width(0)
	, m_Height(0)
	, m_Windowed(0)
{
	m_AppName = L"";
	m_hInstance = nullptr;
	m_Hwnd = nullptr;
}

System::~System()
{
}

bool System::Create(const int& x, const int& y, const bool& windowed)
{
	m_Width = x;
	m_Height = y;
	m_Windowed = windowed;

	return Initialize();
}

void System::ShutDown()
{
	ShowCursor(true);

	if (m_Windowed)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_Hwnd);
	m_Hwnd = NULL;

	UnregisterClass(m_AppName, m_hInstance);
	m_hInstance = NULL;

	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		SAFE_DELETE(m_Graphics);
	}

	if (m_Timer)
	{
		SAFE_DELETE(m_Timer);
	}
}

void System::Generate()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();

			if (!result)
			{
				done = true;
			}
		}

	}
}

LRESULT System::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT System::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN:
		{
			if (VK_ESCAPE == wParam)
			{
				PostQuitMessage(0);
			}
			return 0;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		default:
		{
			return MessageHandler(hWnd, msg, wParam, lParam);
		}
	}
}

bool System::Initialize()
{
	InitializeWindow();

	//Graphics Init
	m_Graphics = new Graphics();
	if (!m_Graphics)
		return false;

	if (!(m_Graphics->Initialize(m_hInstance, m_Hwnd, m_Width, m_Height, m_Windowed)))
		return false;

	//Timer Init
	m_Timer = new Timer();
	if (!m_Timer)
		return false;

	if (!m_Timer->Initialize())
		return false;

	return true;
}

bool System::Frame()
{
	m_Timer->Frame();

	bool result = m_Graphics->Frame(m_Timer->GetTime());
	if (!result)
		return false;

	return true;
}

bool System::InitializeWindow()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	m_hInstance = GetModuleHandle(NULL);

	m_AppName = L"Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_AppName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	DWORD style = 0;

	if (m_Windowed)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

		style = WS_OVERLAPPEDWINDOW;
	}

	m_Hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_AppName, m_AppName,
		style, posX, posY, m_Width, m_Height, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_Hwnd, SW_SHOW);
	SetForegroundWindow(m_Hwnd);
	SetFocus(m_Hwnd);

	ShowCursor(true);


	return true;
}
