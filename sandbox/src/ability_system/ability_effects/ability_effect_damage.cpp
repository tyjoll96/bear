#include "brpch.h"
#include "ability_effect_damage.h"

#include "../../ralleon_components.h"

namespace ralleon
{
	AbilityEffectDamage::AbilityEffectDamage(uint32_t amount, AbilityPen pen, StatNames scaling_stat, float scaling_stat_multiplier, AbilityTarget target)
		: amount_(amount), pen_(pen), scaling_stat_(scaling_stat), scaling_stat_multiplier_(scaling_stat_multiplier), AbilityEffectBase(target)
	{
	}

	void AbilityEffectDamage::AddEffect(entt::registry& registry, entt::entity caster, entt::entity target, Ability* ability)
	{
		// calculate damage based on character stat

		std::cout << "Applying " << amount_ << " of damage." << std::endl;

		auto target_character = &registry.get<CharacterComponent>(target);
		target_character->MissHealth += amount_;

		std::cout << target_character->CurrentHealth() << std::endl;
	}
}