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
		if (!look_for_target) return;

		look_for_target = false;

		entt::entity closest_target = entt::null;
		float closest_target_distance = 50.0f;
		glm::mat4 current_location = player_entity_.GetComponent<bear::TransformComponent>().Transform;

		// exclude targets on cooldown
		auto view = registry.view<CharacterComponent, bear::TransformComponent>();
		for (auto entity : view)
		{
			if (entity == player_entity_.GetEntity()) continue;

			auto transform = registry.get<bear::TransformComponent>(entity);
			float distance = glm::distance(current_location[3], transform.Transform[3]);

			if (distance < closest_target_distance)
			{
				closest_target = entity;
				closest_target_distance = distance;
			}
		}

		if (closest_target == entt::null) return;

		player_entity_.GetComponent<CharacterComponent>().Target = closest_target;

		//target_cooldowns_.push_back({ closest_target, std::chrono::high_resolution_clock::now() });

		// clear outdated target cooldowns
	}

	void TargettingSystem::OnEvent(bear::Event& e)
	{
		bear::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<bear::KeyPressedEvent>(BR_BIND_EVENT_FN(TargettingSystem::OnKeyPressedEvent));
	}

	bool TargettingSystem::OnKeyPressedEvent(bear::KeyPressedEvent& e)
	{
		look_for_target = (e.GetKeyCode() == bear::Key::Tab);

		// escape clear target cooldowns

		return false;
	}
}