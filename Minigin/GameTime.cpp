#include "GameTime.h"

void dae::GameTime::UpdateTime()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
    UpdateFrameRate();
	m_LastTime = m_CurrentTime;
}

void dae::GameTime::UpdateFrameRate()
{
	m_Fps = 1.0 / m_DeltaTime;
	m_AverageFps = m_SmoothFactor * m_Fps + (1 - m_SmoothFactor) * m_AverageFps;
}
