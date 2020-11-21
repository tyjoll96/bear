#pragma once

#include "../ability.h"
#include "ability_effect_base.h"

namespace ralleon
{
	enum class StatNames
	{
		kAttackDamage,
		kArmour,
		kHealthRegen,
		kMagicBoost,
		kMagicResist,
		kSpeed
	};

	class AbilityEffectDamage : public AbilityEffectBase
	{
	public:
		AbilityEffectDamage(uint32_t amount, AbilityPen pen, StatNames scaling_stat, float scaling_stat_multiplier, AbilityTarget target);

		virtual void AddEffect(entt::registry& registry, entt::entity caster, entt::entity target, Ability* ability) override;
		virtual AbilityEffectBase* Multiply(int multiplier) override
		{
			return &AbilityEffectDamage(
				0,
				AbilityPen::Physical,
				StatNames::kAttackDamage,
				1.0f,
				AbilityTarget::kAny
			);
		}
		virtual void RemoveEffect(AbilityCasterComponent* ability_caster, Ability* ability) override {}
	private:
		uint32_t amount_;
		AbilityPen pen_;
		StatNames scaling_stat_;
		float scaling_stat_multiplier_;
	};
}