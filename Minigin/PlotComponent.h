#pragma once
#include <vector>
#include <valarray>

#include "Component.h"

namespace dae
{
	struct TestTransform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		TestTransform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		TestTransform* transform;
		int ID;
	};

	double inline ForwardTransformPlot(double log, void*)
	{
		return std::pow(2, log);
	}

	double inline InverseTransformPlot(double linear, void*)
	{
		return std::log2(linear);
	}

	class PlotComponent : public Component
	{
	public:
		PlotComponent(GameObject* owner);

		void RenderPlot();

	private:
		int m_NrSamplesInt = 10;
		int m_NrSamplesGO = 10;

		std::vector<float> m_StepsizeInt{};
		std::vector<float> m_DurationInt{};

		std::vector<float> m_StepsizeGO{};
		std::vector<float> m_DurationGO{};

		std::vector<float> m_StepsizeAltGO{};
		std::vector<float> m_DurationAltGO{};
	};
}

