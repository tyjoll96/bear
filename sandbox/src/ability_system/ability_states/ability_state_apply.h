#pragma once

#include "ability_state_base.h"

namespace ralleon
{
	class AbilityStateApply : public AbilityStateBase
	{
	public:
		AbilityStateApply();

		virtual void OnEnter(entt::registry& registry, float delta_time, entt::entity caster);
	private:
		void ApplyAbility(entt::registry& registry, entt::entity caster);
	};
}