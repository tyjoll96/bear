#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/quaternion.hpp>

namespace bear
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4 () { return Transform; }
		operator const glm::mat4() const { return Transform; }

		const glm::vec3 Forward() const
		{
			glm::mat4 inverse = glm::inverse(Transform);
			return glm::normalize(glm::vec3(inverse[0][2], inverse[1][2], inverse[2][2]));
		}

		const glm::vec3 Right() const
		{
			glm::mat4 inverse = glm::inverse(Transform);
			return glm::normalize(glm::vec3(inverse[0][0], inverse[1][0], inverse[2][0]));
		}

		const glm::vec3 GetPosition() const { return position_; }
		void SetPosition(const glm::vec3& position) { position_ = position; CalculateMatrix(); }

		const glm::quat GetRotation() const { return rotation_; }
		void SetRotation(const glm::quat& rotation) { rotation_ = rotation; CalculateMatrix(); }

		const glm::vec3 GetScale() const { return scale_; }
		void SetScale(const glm::vec3& scale) { scale_ = scale; CalculateMatrix(); }
	private:
		void CalculateMatrix()
		{
			glm::mat4 new_mat = glm::mat4(1.0f);
			new_mat = glm::translate(new_mat, position_);
			new_mat = new_mat * glm::toMat4(rotation_);
			new_mat = glm::scale(new_mat, scale_);

			Transform = new_mat;
		}
		glm::vec3 position_ = glm::vec3(0.0f);
		glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 scale_ = glm::vec3(1.0f);
	};
}