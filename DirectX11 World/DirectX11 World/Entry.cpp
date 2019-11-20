#include "PCH.h"
#include "System.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanc, LPSTR CmdParam, int nCmdShow)
{
	System* m_System;
	bool result;

	m_System = new System();
	if (m_System->Create(1920, 1080, 1))
		m_System->Generate();

	m_System->ShutDown();
	SAFE_DELETE(m_System);

	return 0;
}