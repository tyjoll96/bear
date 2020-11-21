#include "brpch.h"
#include "camera_follow_system.h"

namespace ralleon
{
	void CameraFollowSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		bear::TransformComponent* follow_transform = nullptr;
		bear::TransformComponent* camera_transform = nullptr;

		auto camera_follow_view = registry.view<CameraFollowComponent, bear::TransformComponent>();
		for (auto entity : camera_follow_view)
		{
			follow_transform = &registry.get<bear::TransformComponent>(entity);
			auto camera_handle = registry.get<CameraFollowComponent>(entity);
			camera_transform = &camera_handle.Camera.GetComponent<bear::TransformComponent>();
		}

		if (!follow_transform || !camera_transform) return;

		/*follow_transform->Transform = glm::translate(follow_transform->Transform, glm::vec3{ 0.0f, 0.0f, -5.0f } *delta_time);
		follow_transform->Transform = glm::rotate(follow_transform->Transform, glm::radians(-45.0f * delta_time), glm::vec3{ 0.0f, 1.0f, 0.0f });*/
		glm::mat4 eye = glm::translate(follow_transform->Transform, { 0.0f, 2.0f, 10.0f });
		camera_transform->Transform = glm::lookAt(glm::vec3(eye[3]), glm::vec3(follow_transform->Transform[3]), { 0.0f, 1.0f, 0.0f });
	}
}