#include "PlotComponent.h"

#include "chrono"

#include "imgui.h"
#include "implot.h"


dae::PlotComponent::PlotComponent(GameObject* owner):
Component(owner)
{
}


void dae::PlotComponent::RenderPlot()
{
    ImGui::Begin("Exercise 1");
    ImGui::InputInt("# samples", &m_NrSamplesInt);

    if (ImGui::Button("Trash the cache"))
    {
        m_StepsizeInt.clear();
        m_DurationInt.clear();

        constexpr int size = 1 << 23;
        int* buffer = new int[size] {};

        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            long long avgDuration{};
            long long topOutlier{};
            long long bottomOutlier = std::numeric_limits<long long>::max();

            for (int j{}; j < m_NrSamplesInt; ++j)
            {
                const auto start = std::chrono::steady_clock::now();
                for (int i = 0; i < size; i += stepsize)
                {
                    buffer[i] *= 2;
                }
                const auto end = std::chrono::steady_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                avgDuration += duration;
                if (duration > topOutlier) topOutlier = duration;
                if (duration < bottomOutlier) bottomOutlier = duration;
            }
            avgDuration -= topOutlier;
            avgDuration -= bottomOutlier;
            avgDuration /= (m_NrSamplesInt - 2);

            m_StepsizeInt.push_back(static_cast<float>(stepsize));
            m_DurationInt.push_back(static_cast<float>(avgDuration));
        }

        delete[] buffer;
    }

    if(!m_StepsizeInt.empty() && !m_DurationInt.empty())
    {
	    if(ImPlot::BeginPlot("Int"))
	    {
		    ImPlot::SetupAxes("Stepsize", "ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
	    	ImPlot::SetupAxisScale(ImAxis_X1, InverseTransformPlot, ForwardTransformPlot);

	    	ImPlot::PlotLine("Int", m_StepsizeInt.data(), m_DurationInt.data(), static_cast<int>(m_StepsizeInt.size()));
	    	ImPlot::EndPlot();
	    }
    }
    ImGui::End();


    ImGui::Begin("Exercise 2");
    ImGui::InputInt("# samples", &m_NrSamplesGO);

    if (ImGui::Button("Trash the cache GameObject"))
    {
        m_StepsizeInt.clear();
        m_DurationInt.clear();

        constexpr int size = 1 << 23;
        GameObject3D* buffer = new GameObject3D[size] {};

        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            long long avgDuration{};
            long long topOutlier{};
            long long bottomOutlier = std::numeric_limits<long long>::max();

            for (int j{}; j < m_NrSamplesGO; ++j)
            {
                const auto start = std::chrono::steady_clock::now();
                for (int i = 0; i < size; i += stepsize)
                {
                    buffer[i].ID *= 2;
                }
                const auto end = std::chrono::steady_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                avgDuration += duration;
                if (duration > topOutlier) topOutlier = duration;
                if (duration < bottomOutlier) bottomOutlier = duration;
            }
            avgDuration -= topOutlier;
            avgDuration -= bottomOutlier;
            avgDuration /= (m_NrSamplesInt - 2);

            m_StepsizeGO.push_back(static_cast<float>(stepsize));
            m_DurationGO.push_back(static_cast<float>(avgDuration));
        }

        delete[] buffer;
    }

    if (!m_StepsizeGO.empty() && !m_DurationGO.empty())
    {
        if (ImPlot::BeginPlot("GameObject"))
        {
            ImPlot::SetupAxes("Stepsize", "ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, InverseTransformPlot, ForwardTransformPlot);

            ImPlot::PlotLine("GameObject", m_StepsizeGO.data(), m_DurationGO.data(), static_cast<int>(m_StepsizeGO.size()));
            ImPlot::EndPlot();
        }
    }

    if (ImGui::Button("Trash the cache GameObjectAlt"))
    {
        m_StepsizeInt.clear();
        m_DurationInt.clear();

        constexpr int size = 1 << 23;
        GameObject3DAlt* buffer = new GameObject3DAlt[size]{};

        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            long long avgDuration{};
            long long topOutlier{};
            long long bottomOutlier = std::numeric_limits<long long>::max();

            for (int j{}; j < m_NrSamplesGO; ++j)
            {
                const auto start = std::chrono::steady_clock::now();
                for (int i = 0; i < size; i += stepsize)
                {
                    buffer[i].ID *= 2;
                }
                const auto end = std::chrono::steady_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                avgDuration += duration;
                if (duration > topOutlier) topOutlier = duration;
                if (duration < bottomOutlier) bottomOutlier = duration;
            }
            avgDuration -= topOutlier;
            avgDuration -= bottomOutlier;
            avgDuration /= (m_NrSamplesInt - 2);

            m_StepsizeAltGO.push_back(static_cast<float>(stepsize));
            m_DurationAltGO.push_back(static_cast<float>(avgDuration));
        }

        delete[] buffer;
    }

    if (!m_StepsizeAltGO.empty() && !m_DurationAltGO.empty())
    {
        if (ImPlot::BeginPlot("GameObjectAlt"))
        {
            ImPlot::SetupAxes("Stepsize", "ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, InverseTransformPlot, ForwardTransformPlot);

            ImPlot::PlotLine("GameObjectAlt", m_StepsizeAltGO.data(), m_DurationAltGO.data(), static_cast<int>(m_StepsizeAltGO.size()));
            ImPlot::EndPlot();
        }
    }

    if (!m_StepsizeGO.empty() && !m_DurationGO.empty() && !m_StepsizeAltGO.empty() && !m_DurationAltGO.empty())
    {
        if (ImPlot::BeginPlot("Combined"))
        {
            ImPlot::SetupAxes("Stepsize", "ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, InverseTransformPlot, ForwardTransformPlot);

            ImPlot::PlotLine("GameObject", m_StepsizeGO.data(), m_DurationGO.data(), static_cast<int>(m_StepsizeGO.size()));
            ImPlot::PlotLine("GameObjectAlt", m_StepsizeAltGO.data(), m_DurationAltGO.data(), static_cast<int>(m_StepsizeAltGO.size()));
        	ImPlot::EndPlot();
        }
    }
    ImGui::End();
}
