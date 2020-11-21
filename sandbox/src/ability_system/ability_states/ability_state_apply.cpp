#include "brpch.h"
#include "ability_state_apply.h"

#include "../ability_caster_component.h"

namespace ralleon
{
	AbilityStateApply::AbilityStateApply()
	{
	}

	void AbilityStateApply::OnEnter(entt::registry& registry, float delta_time, entt::entity caster)
	{
		SetupNewState(registry, caster, AbilityState::kApply);

		ApplyAbility(registry, caster);

		GoNextState(registry, delta_time, caster);
	}

	void AbilityStateApply::ApplyAbility(entt::registry& registry, entt::entity caster)
	{
		auto ability_caster = &registry.get<AbilityCasterComponent>(caster);
		ability_caster->Cooldowns[ability_caster->CurrentAbilityIndex]
			= std::chrono::high_resolution_clock::now() + ability_caster->CurrentAbility()->GetCooldown();

		auto target_ability_caster = &registry.get<AbilityCasterComponent>(ability_caster->Target);
		target_ability_caster->IncomingAbilities.push_back(std::make_tuple(ability_caster->CurrentAbility(), caster));

		std::cout << "Ability has been applied." << std::endl;
	}
}