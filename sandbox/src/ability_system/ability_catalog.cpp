#include "ability_catalog.h"

#include "ability_effects/ability_effect_damage.h"

#include "ability_states/ability_state_base.h"
#include "ability_states/ability_state_check.h"
#include "ability_states/ability_state_animation_pre_apply.h"
#include "ability_states/ability_state_apply.h"
#include "ability_states/ability_state_animation_post_apply.h"

namespace ralleon
{
	static Ability* unarmed_auto_attack;

	void AbilityCatalog::Init()
	{
		unarmed_auto_attack = new Ability(
			0,
			std::string("Unarmed Auto Attack"),
			5.0f,
			std::vector<std::shared_ptr<AbilityEffectBase>> {
				std::make_shared<AbilityEffectDamage>(AbilityEffectDamage(
					15,
					AbilityPen::Physical,
					StatNames::kAttackDamage,
					1.0f,
					AbilityTarget::kEnemy
				)),
			},
			std::map<AbilityState, std::shared_ptr<AbilityStateBase>> {
				{ AbilityState::kCheck, std::make_shared<AbilityStateCheck>(AbilityStateCheck(25.0f)) },
				{ AbilityState::kAnimationPreApply, std::make_shared<AbilityStateAnimationPreApply>(AbilityStateAnimationPreApply(std::chrono::seconds(2))) },
				{ AbilityState::kAnimationPostApply, std::make_shared<AbilityStateAnimationPostApply>(AbilityStateAnimationPostApply(std::chrono::seconds(2))) },
				{ AbilityState::kApply, std::make_shared<AbilityStateApply>() },
			}
		);
	}

	Ability* AbilityCatalog::UnarmedAutoAttack() { return unarmed_auto_attack; }
}