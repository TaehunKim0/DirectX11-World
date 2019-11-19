#include "PCH.h"
#include "Timer.h"

Timer::Timer()
{
	m_FrameTime = 0;
	m_Frequency = 0;
	m_StartTime = 0;
	m_TicksPerMs = 0;
}

Timer::~Timer()
{
}

bool Timer::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)& m_Frequency);
	if (m_Frequency == 0)
	{
		return false;
	}

	m_TicksPerMs = (float)(m_Frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)& m_StartTime);

	return true;
}

void Timer::Frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_StartTime);

	m_FrameTime = timeDifference / m_TicksPerMs;

	m_StartTime = currentTime;
}

float Timer::GetTime()
{
	return m_FrameTime;
}