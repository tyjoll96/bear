#pragma once

#include "ability_state_base.h"

namespace ralleon
{
	class AbilityStateCast : public AbilityStateBase
	{
	public:
		AbilityStateCast(std::chrono::steady_clock::duration state_duration);

		virtual void OnEnter(entt::registry& registry, float delta_time, entt::entity caster) override;
	protected:
		std::chrono::steady_clock::duration state_duration_;
	};
}