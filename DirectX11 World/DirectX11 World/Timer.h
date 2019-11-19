#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	bool Initialize();
	void Frame();

	float GetTime();

private:
	INT64 m_Frequency;
	float m_TicksPerMs;
	INT64 m_StartTime;
	float m_FrameTime;
};