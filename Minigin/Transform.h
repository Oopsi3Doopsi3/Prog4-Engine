#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3 pos);

		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; };
		void SetWorldPosition(const glm::vec3 pos);

		void SetPositionDirty();
		void SetPositionClean();
		bool GetPositionIsDirty() const { return m_PositionIsDirty; }
	private:
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

		bool m_PositionIsDirty{true};
	};
}
