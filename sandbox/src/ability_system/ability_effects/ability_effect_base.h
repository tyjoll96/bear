#pragma once

#include <entt.hpp>

namespace ralleon
{
	enum class AbilityTarget;
	class Ability;
	class AbilityCasterComponent;
	class AbilityEffectBase
	{
	public:
		AbilityEffectBase(AbilityTarget target) : target_(target) {}
		virtual ~AbilityEffectBase() = default;

		virtual void AddEffect(entt::registry& registry, entt::entity caster, entt::entity target, Ability* ability) = 0;
		virtual AbilityEffectBase* Multiply(int multiplier) = 0;
		virtual void RemoveEffect(AbilityCasterComponent* ability_caster, Ability* ability) = 0;
	protected:
		AbilityTarget target_;
	};
}