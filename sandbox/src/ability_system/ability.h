#pragma once

#include <string>
#include <map>
#include <memory>

#include "ability_effects/ability_effect_base.h"
#include "ability_states/ability_state_base.h"

namespace ralleon
{
	enum class AbilityPen
	{
		Composite,
		Magical,
		Physical
	};

	enum class AbilityState
	{
		kWait,
		kCheck,
		kCast,
		kAnimationPreApply,
		kApply,
		kAnimationPostApply,
	};

	enum class AbilityTarget
	{
		kAny,
		kAlly,
		kEnemy,
		kSelf
	};

	class Ability
	{
	public:
		Ability(uint8_t id, std::string& name);
		/*Ability(AbilityBuilder& builder)
		{

		}*/
		Ability(
			uint8_t id,
			std::string& name,
			float cooldown,
			std::vector<std::shared_ptr<AbilityEffectBase>>& ability_effects,
			std::map<AbilityState, std::shared_ptr<AbilityStateBase>>& ability_states);

		AbilityState GetNextState(AbilityState current_state);

		std::vector<std::shared_ptr<AbilityEffectBase>> GetAbilityEffects() const { return ability_effects_; }
		std::map<AbilityState, std::shared_ptr<AbilityStateBase>> GetAbilityStates() const { return ability_states_; }
		std::chrono::steady_clock::duration GetCooldown() const { return cooldown_; }
	private:
		uint8_t id_;
		std::string name_;

		std::vector<std::shared_ptr<AbilityEffectBase>> ability_effects_;
		std::map<AbilityState, std::shared_ptr<AbilityStateBase>> ability_states_;
		std::chrono::steady_clock::duration cooldown_ = std::chrono::steady_clock::duration::min();
	};

	/*class AbilityBuilder
	{
	friend class Ability;
	public:
		AbilityBuilder(std::string& name)
			: name_(name)
		{
		}

		Ability Build() { return Ability(this); }

		AbilityBuilder WithAbilityStates(std::map<AbilityState, AbilityStateBase*>& ability_states)
		{
			ability_states_ = ability_states;
		}
	private:
		std::map<AbilityState, AbilityStateBase> ability_states_;
		std::string name_;
	};*/
}