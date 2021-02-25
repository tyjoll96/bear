#include "brpch.h"
#include "ability_state_animation_post_apply.h"

#include "../ability.h"
#include "../castbar_component.h"

namespace ralleon
{
	AbilityStateAnimationPostApply::AbilityStateAnimationPostApply(std::chrono::steady_clock::duration state_duration)
		: AbilityStateAnimationPreApply(state_duration) {}

	void AbilityStateAnimationPostApply::OnEnter(entt::registry& registry, float delta_time, entt::entity caster)
	{
		SetupNewState(registry, caster, AbilityState::kAnimationPostApply, state_duration_);
	}
}