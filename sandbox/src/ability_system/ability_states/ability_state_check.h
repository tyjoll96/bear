#pragma once

#include "ability_state_base.h"

namespace ralleon
{
	class AbilityStateCheck : public AbilityStateBase
	{
	public:
		AbilityStateCheck() = default;
		AbilityStateCheck(float range) : range_(range) {}
		virtual void OnUpdate(entt::registry& registry, float delta_time, entt::entity caster) override;

		float GetRange() const { return range_; }
	private:
		float range_ = 5.0f;
	};
}