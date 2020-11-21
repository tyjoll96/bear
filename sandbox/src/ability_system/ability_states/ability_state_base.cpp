#include "brpch.h"
#include "ability_state_base.h"

#include "../ability.h"
#include "../ability_caster_component.h"

namespace ralleon
{
	void AbilityStateBase::OnEnter(entt::registry& registry, float delta_time, entt::entity caster)
	{
	}

	void AbilityStateBase::OnUpdate(entt::registry& registry, float delta_time, entt::entity caster)
	{
		auto ability_caster = registry.get<AbilityCasterComponent>(caster);

		if (std::chrono::high_resolution_clock::now() < ability_caster.StateFinish) return;

		GoNextState(registry, delta_time, caster);
	}

	void AbilityStateBase::GoNextState(entt::registry& registry, float delta_time, entt::entity caster)
	{
		auto ability_caster = &registry.get<AbilityCasterComponent>(caster);
		AbilityState next_state = ability_caster->CurrentAbility()->GetNextState(ability_caster->State);

		if (next_state == AbilityState::kWait)
		{
			ability_caster->State = AbilityState::kWait;
			return;
		}

		ability_caster->CurrentAbility()->GetAbilityStates()[next_state]->OnEnter(registry, delta_time, caster);
	}

	void AbilityStateBase::SetupNewState(
		entt::registry& registry,
		entt::entity caster,
		AbilityState new_state,
		std::chrono::steady_clock::duration new_state_length)
	{
		auto ability_caster = &registry.get<AbilityCasterComponent>(caster);

		ability_caster->StateFinish = ability_caster->StateFinish + new_state_length;
		ability_caster->State = new_state;
	}
}