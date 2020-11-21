#include "brpch.h"
#include "ability_system.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "bear/core/core.h"
#include "bear/scene/components.h"

#include "ability_states/ability_state_base.h"
#include "../ralleon_components.h"

namespace ralleon
{
	AbilityCastingSystem::AbilityCastingSystem(bear::EntityHandle& player_entity, const std::string& name)
		: System(name), player_entity_(player_entity)
	{
	}

	void AbilityCastingSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		auto view = registry.view<AbilityCasterComponent>();
		for (auto entity : view)
		{
			auto ability_caster = &registry.get<AbilityCasterComponent>(entity);

			while (!ability_caster->IncomingAbilities.empty())
			{
				auto [ability, caster] = ability_caster->IncomingAbilities.back();

				for (auto ability_effect : ability->GetAbilityEffects())
				{
					ability_effect->AddEffect(registry, caster, entity, ability);
				}

				ability_caster->IncomingAbilities.pop_back();
			}

			if (ability_caster->State == AbilityState::kWait)
			{
				// Try auto attack.
				continue;
			}

			ability_caster->CurrentAbility()->GetAbilityStates()[ability_caster->State]->OnUpdate(registry, delta_time, entity);
		}
	}

	void AbilityCastingSystem::OnEvent(bear::Event& e)
	{
		bear::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<bear::KeyPressedEvent>(BR_BIND_EVENT_FN(AbilityCastingSystem::OnKeyPressedEvent));
	}

	bool AbilityCastingSystem::OnKeyPressedEvent(bear::KeyPressedEvent& e)
	{
		auto ability_caster = player_entity_.GetComponentRef<AbilityCasterComponent>();

		if (ability_caster->State != AbilityState::kWait) return false;

		auto character = player_entity_.GetComponentRef<CharacterComponent>();

		if (character->Target == entt::null) return false;

		if (e.GetKeyCode() == bear::Key::D1)
		{
			ability_caster->CurrentAbilityIndex = 0;
			ability_caster->Target = character->Target;
			ability_caster->StateFinish = std::chrono::high_resolution_clock::now();
			ability_caster->State = AbilityState::kCheck;
		}

		return false;
	}

	void AbilityCastingSystem::ClearCurrentAbilityCast(AbilityCasterComponent* ability_caster)
	{
		ability_caster->CurrentAbilityIndex = -1;
		ability_caster->State = AbilityState::kWait;
	}
}