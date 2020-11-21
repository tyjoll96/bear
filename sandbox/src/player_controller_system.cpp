#include "brpch.h"
#include "player_controller_system.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ralleon
{
	void PlayerControllerSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		glm::vec3 move_input = glm::vec3(0.0f);
		move_input.z = -1.0f * bear::Input::IsKeyPressed(bear::Key::W) + 1.0f * bear::Input::IsKeyPressed(bear::Key::S);
		move_input.x = 1.0f * bear::Input::IsKeyPressed(bear::Key::D) + -1.0f * bear::Input::IsKeyPressed(bear::Key::A);
		float rotation = 0.0f;
		rotation = -1.0f * bear::Input::IsKeyPressed(bear::Key::E) + 1.0f * bear::Input::IsKeyPressed(bear::Key::Q);

		auto view = registry.view<PlayerControllerComponent, bear::TransformComponent>();
		for (auto entity : view)
		{
			auto [transform, player_controller] = registry.get<bear::TransformComponent, PlayerControllerComponent>(entity);
			transform.Transform = glm::translate(transform.Transform, move_input * player_controller.MoveSpeed * delta_time);
			transform.Transform = glm::rotate(
				transform.Transform,
				glm::radians(rotation * player_controller.RotationSpeed * delta_time),
				{ 0.0f, 1.0f, 0.0f });
		}
	}
}