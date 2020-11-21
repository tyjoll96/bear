#pragma once

#include "ability_state_animation_pre_apply.h"

namespace ralleon
{
	class AbilityStateAnimationPostApply : public AbilityStateAnimationPreApply
	{
	public:
		AbilityStateAnimationPostApply(std::chrono::steady_clock::duration state_duration);

		virtual void OnEnter(entt::registry& registry, float delta_time, entt::entity caster) override;
	};
}