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
		bool IsActive = true;
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		const glm::vec3 Forward() const { return rotation_ * glm::vec3(0.0f, 0.0f, -1.0f); }

		const glm::vec3 Right() const { return rotation_ * glm::vec3(1.0f, 0.0f, 0.0f); }

		const glm::vec3 Up() const { return rotation_ * glm::vec3(0.0f, 1.0f, 0.0f); }

		void LookAt(const glm::vec3& center, const glm::vec3& up)
		{
			glm::vec3 direction = glm::normalize(center - position_);
			glm::quat q = glm::quatLookAt(direction, up);
			rotation_ = q;
			CalculateMatrix();
		}

		const glm::mat4 GetTransform() const { return transform_; }

		const glm::vec3 GetPosition() const { return position_; }
		void SetPosition(const glm::vec3& position) { position_ = position; CalculateMatrix(); }

		const glm::quat GetRotation() const { return rotation_; }
		void SetRotation(const glm::quat& rotation) { rotation_ = rotation; CalculateMatrix(); }

		const glm::vec3 GetScale() const { return scale_; }
		void SetScale(const glm::vec3& scale) { scale_ = scale; CalculateMatrix(); }
	protected:
		virtual void CalculateMatrix()
		{
			glm::mat4 new_mat = glm::mat4(1.0f);
			new_mat = glm::translate(new_mat, position_);
			new_mat = new_mat * glm::toMat4(rotation_);
			new_mat = glm::scale(new_mat, scale_);
			transform_ = new_mat;
		}

		glm::mat4 transform_ = glm::mat4(1.0f);

		glm::vec3 position_ = glm::vec3(0.0f);
		glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 scale_ = glm::vec3(1.0f);

		//entt::entity parent;
	};

	struct RectTransformComponent : public TransformComponent
	{
		RectTransformComponent() { CalculateMatrix(); };
		RectTransformComponent(const RectTransformComponent&) = default;

		float GetHeight() const { return height_; }
		void SetHeight(float height) { height_ = height; CalculateMatrix(); }

		float GetWidth() const { return width_; }
		void SetWidth(float width) { width_ = width; CalculateMatrix(); }
	protected:
		virtual void CalculateMatrix() override
		{
			glm::mat4 new_mat = glm::mat4(1.0f);
			new_mat = glm::translate(new_mat, position_);
			new_mat = new_mat * glm::toMat4(rotation_);
			new_mat = glm::scale(new_mat, scale_);
			new_mat = glm::scale(new_mat, { width_, height_, 1.0f });

			transform_ = new_mat;
		}
		float height_ = 100.0f;
		float width_ = 100.0f;
	};
}