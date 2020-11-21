#include "brpch.h"
#include "ability.h"

namespace ralleon
{
	Ability::Ability(uint8_t id, std::string& name)
		: id_(id), name_(name) {}

	Ability::Ability(
		uint8_t id,
		std::string& name,
		float cooldown,
		std::vector<std::shared_ptr<AbilityEffectBase>>& ability_effects,
		std::map<AbilityState, std::shared_ptr<AbilityStateBase>>& ability_states)
		: id_(id), name_(name), ability_effects_(ability_effects), ability_states_(ability_states)
	{
		cooldown_ = std::chrono::milliseconds((int)(cooldown * 1000));
	}

	AbilityState Ability::GetNextState(AbilityState current_state)
	{
		if (ability_states_.empty()) return AbilityState::kWait;
		if (current_state == ability_states_.rbegin()->first) return AbilityState::kWait;

		std::map<AbilityState, std::shared_ptr<AbilityStateBase>>::iterator it = ability_states_.find(current_state);
		++it;

		return it->first;
	}
}