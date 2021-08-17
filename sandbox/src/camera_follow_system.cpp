#include "brpch.h"
#include "camera_follow_system.h"

namespace ralleon
{
	void CameraFollowSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		bear::TransformComponent* follow_transform = nullptr;
		bear::TransformComponent* camera_transform = nullptr;
		glm::vec3 offset(0.0f);
		bear::PerspectiveCameraComponent* p_camera = nullptr;

		auto camera_follow_view = registry.view<CameraFollowComponent, bear::TransformComponent>();
		for (auto entity : camera_follow_view)
		{
			follow_transform = &registry.get<bear::TransformComponent>(entity);
			auto camera_handle = registry.get<CameraFollowComponent>(entity);
			camera_transform = &camera_handle.Camera.GetComponent<bear::TransformComponent>();
			offset = camera_handle.Offset;
			p_camera = &camera_handle.Camera.GetComponent<bear::PerspectiveCameraComponent>();
		}

		if (!follow_transform || !camera_transform) return;

		glm::vec3 new_pos = { 0.0f, 4.0f, 0.0f }; // follow_transform->GetPosition() + follow_transform->Forward() * offset.z + follow_transform->Up() * offset.y;
		camera_transform->SetPosition(new_pos);
		/*glm::mat4 new_rot = glm::lookAt(new_pos, follow_transform->GetPosition(), { 0.0f, 1.0f, 0.0f });
		camera_transform->SetRotation(glm::quat_cast(new_rot));*/
		//camera_transform->SetPosition({ 0.0f, -3.0f, -5.0f });
		//p_camera->View = eye;
	}
}