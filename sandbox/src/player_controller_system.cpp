#include "brpch.h"
#include "player_controller_system.h"

#include <glm/gtc/matrix_transform.hpp>

#include "bear/physics/physics_components.h"

namespace ralleon
{
	void PlayerControllerSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		glm::vec3 move_input(0.0f);
		move_input.z = 1.0f * bear::Input::IsKeyPressed(bear::Key::W) + -1.0f * bear::Input::IsKeyPressed(bear::Key::S);
		move_input.y = 1.0 * bear::Input::IsKeyPressed(bear::Key::Space);
		move_input.x = 1.0f * bear::Input::IsKeyPressed(bear::Key::D) + -1.0f * bear::Input::IsKeyPressed(bear::Key::A);
		float rotation = -1.0f * bear::Input::IsKeyPressed(bear::Key::E) + 1.0f * bear::Input::IsKeyPressed(bear::Key::Q);

		auto view = registry.view<PlayerControllerComponent, bear::TransformComponent>();
		for (auto entity : view)
		{
			auto [transform, player_controller] = registry.get<bear::TransformComponent, PlayerControllerComponent>(entity);
			transform.SetPosition(
				transform.GetPosition()
				+ (transform.Forward() * move_input.z + glm::vec3(0.0f, move_input.y, 0.0f) + transform.Right() * move_input.x)
				* player_controller.MoveSpeed * delta_time);

			transform.SetRotation(
				glm::quat(glm::vec3(0.0f, 1.0f, 0.0f) * glm::radians(rotation * player_controller.RotationSpeed * delta_time))
				* transform.GetRotation());

			/*if (registry.has<bear::RigidBodyComponent>(entity))
			{
				if (bear::Input::IsKeyPressed(bear::Key::Space))
				{
					auto rigid_body = registry.get<bear::RigidBodyComponent>(entity);
					rigid_body.RigidBody->applyForceToCenterOfMass({ 0.0f, 5.0f, 0.0f });
				}
			}*/
		}
	}
}