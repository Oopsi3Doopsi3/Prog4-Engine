#pragma once
#include <chrono>

namespace dae
{
	class GameTime final
	{
		friend class Minigin;
	public:
		static float GetDeltaTime() { return m_DeltaTime; }
		static double GetAverageFps() { return m_AverageFps; }
		static std::chrono::steady_clock::time_point GetCurTime() { return m_CurrentTime; }

	protected:
		static void UpdateTime();
		

	private:
		inline static std::chrono::steady_clock::time_point m_CurrentTime;
		inline static float m_DeltaTime{0.0};
		inline static std::chrono::steady_clock::time_point m_LastTime = std::chrono::high_resolution_clock::now();
		inline static double m_Fps{0.0};
		inline static double m_AverageFps{ 0.0 };
		inline static double m_SmoothFactor{ 0.1 };

		static void UpdateFrameRate();
	};
}
