#include "brpch.h"
#include "camera_follow_system.h"

#include <imgui/imgui.h>

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

		glm::mat4 eye = glm::translate(follow_transform->GetTransform(), offset);
		camera_transform->SetPosition(eye[3]);
		new_pos_ = eye[3];
		p_camera->View = glm::lookAt(glm::vec3(eye[3]), glm::vec3(follow_transform->GetTransform()[3]), { 0.0f, 1.0f, 0.0f });
	}
	void CameraFollowSystem::OnImGuiUpdate()
	{
		ImGui::Begin("Camera follow system");
		ImGui::Text("%.3f", new_pos_.x);
		ImGui::Text("%.3f", new_pos_.y);
		ImGui::Text("%.3f", new_pos_.z);
		ImGui::End();
	}
}