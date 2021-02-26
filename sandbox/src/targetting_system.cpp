#include "brpch.h"
#include "targetting_system.h"

#include "bear/core/key_codes.h"

namespace ralleon
{
	TargettingSystem::TargettingSystem(bear::EntityHandle& player_entity, const std::string& name)
		: System(name), player_entity_(player_entity)
	{
		if (!player_entity_.HasComponent<CharacterComponent>())
			player_entity_.AddComponent<CharacterComponent>();

		if (!player_entity_.HasComponent<bear::TransformComponent>())
			player_entity_.AddComponent<bear::TransformComponent>();
	}

	void TargettingSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		if (!look_for_target_) return;

		look_for_target_ = false;

		entt::entity closest_target = entt::null;
		float closest_target_distance = 50.0f;
		glm::vec3 current_location = player_entity_.GetComponent<bear::TransformComponent>().GetPosition();

		// exclude targets on cooldown
		{
			auto view = registry.view<CharacterComponent, bear::TransformComponent>();
			for (auto entity : view)
			{
				if (entity == player_entity_.GetEntity()) continue;

				const auto& transform = registry.get<bear::TransformComponent>(entity);
				float distance = glm::distance(current_location, transform.GetPosition());

				if (distance < closest_target_distance)
				{
					closest_target = entity;
					closest_target_distance = distance;
				}
			}
		}

		if (closest_target == entt::null) return;

		CharacterComponent* player_character = &player_entity_.GetComponent<CharacterComponent>();

		player_character->Target = closest_target;

		//target_cooldowns_.push_back({ closest_target, std::chrono::high_resolution_clock::now() });

		// clear outdated target cooldowns

		// Move target indicator entity to target
		{
			auto view = registry.view<TargetIndicatorComponent, bear::TransformComponent>();
			for (auto entity : view)
			{
				bear::TransformComponent* indicator_transform = &registry.get<bear::TransformComponent>(entity);
				const auto& target_transform = registry.get<bear::TransformComponent>(player_character->Target);
				indicator_transform->SetPosition(target_transform.GetPosition());
			}

		}
	}

	void TargettingSystem::OnEvent(bear::Event& e)
	{
		bear::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<bear::KeyPressedEvent>(BR_BIND_EVENT_FN(TargettingSystem::OnKeyPressedEvent));
	}

	bool TargettingSystem::OnKeyPressedEvent(bear::KeyPressedEvent& e)
	{
		look_for_target_ = (e.GetKeyCode() == bear::Key::Tab);

		// escape clear target cooldowns

		return false;
	}

	bool TargettingSystem::OnMouseButtonPressedEvent(bear::MouseButtonPressedEvent& e)
	{

		return false;
	}
}