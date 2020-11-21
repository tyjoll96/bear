#pragma once

#include <string>
#include <chrono>

#include "bear.h"
#include "bear/events/key_event.h"

#include "ability.h"
#include "ability_caster_component.h"
#include "ability_catalog.h"

namespace ralleon
{
	class AbilityCastingSystem : public bear::System
	{
	public:
		AbilityCastingSystem(bear::EntityHandle& player_entity, const std::string& name = "Ability system");
		virtual ~AbilityCastingSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
		virtual void OnEvent(bear::Event& e);

		bool OnKeyPressedEvent(bear::KeyPressedEvent& e);
	private:
		void ClearCurrentAbilityCast(AbilityCasterComponent* ability_caster);
		bear::EntityHandle player_entity_;
	};
}