#pragma once

#include "Timer.h"
#include "Graphics.h"

class System
{
private:
	LPCWSTR m_AppName;
	HINSTANCE m_hInstance;
	HWND m_Hwnd;

	UINT m_Width;
	UINT m_Height;
	BOOL m_Windowed;

private:
	Graphics* m_Graphics;
	Timer* m_Timer;

public:
	System();
	~System();

	bool Create(const int& x, const int& y, const bool& windowed);
	void ShutDown();
	void Generate();

	static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool Initialize();
	bool Frame();
	bool InitializeWindow();
};