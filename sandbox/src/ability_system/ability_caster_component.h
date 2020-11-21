#pragma once

#include <chrono>

#include "ability.h"
#include "ability_catalog.h"

namespace ralleon
{
	struct AbilityCasterComponent
	{
		int8_t CurrentAbilityIndex = -1; // remove?
		Ability* LearnedAbilities = std::array<Ability*, 2>{ AbilityCatalog::UnarmedAutoAttack(), AbilityCatalog::UnarmedAutoAttack() }[0];
		std::chrono::steady_clock::time_point Cooldowns[4] = { std::chrono::steady_clock::time_point::min() };

		AbilityState State = AbilityState::kWait;
		std::chrono::steady_clock::time_point StateFinish = std::chrono::steady_clock::time_point::min();

		entt::entity Target = entt::null;

		std::vector<std::tuple<Ability*, entt::entity>> IncomingAbilities;

		Ability* CurrentAbility() const { return &LearnedAbilities[CurrentAbilityIndex]; }

		AbilityCasterComponent() = default;
		AbilityCasterComponent(const AbilityCasterComponent&) = default;
		AbilityCasterComponent(Ability* learned_abilities)
			: LearnedAbilities(learned_abilities) {}
	};
}