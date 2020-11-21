#include "brpch.h"
#include "ability_state_animation_pre_apply.h"

#include "../ability.h"

namespace ralleon
{
	AbilityStateAnimationPreApply::AbilityStateAnimationPreApply(std::chrono::steady_clock::duration state_duration)
		: state_duration_(state_duration) {}

	void AbilityStateAnimationPreApply::OnEnter(entt::registry& registry, float delta_time, entt::entity caster)
	{
		SetupNewState(registry, caster, AbilityState::kAnimationPreApply, state_duration_);
	}
}