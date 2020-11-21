#pragma once

#include <chrono>

#include <entt.hpp>

#include "bear.h"
#include "bear/events/key_event.h"

#include "ralleon_components.h"

namespace ralleon
{
	struct TargetCooldown
	{
		entt::entity Entity;
		std::chrono::steady_clock::time_point EndOfCooldown;
	};

	class TargettingSystem : public bear::System
	{
	public:
		TargettingSystem(bear::EntityHandle& player_entity, const std::string& name = "Targetting system");
		virtual ~TargettingSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
		virtual void OnEvent(bear::Event& e);

		bool OnKeyPressedEvent(bear::KeyPressedEvent& e);
	private:
		bear::EntityHandle player_entity_;

		bool look_for_target = false;

		//std::vector<TargetCooldown> target_cooldowns_;
	};
}