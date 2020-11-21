#pragma once

#include <chrono>

#include <entt.hpp>

#include "bear.h"

namespace ralleon
{
	enum class AbilityState;
	class AbilityStateBase
	{
	public:
		AbilityStateBase() {}
		virtual ~AbilityStateBase() = default;

		virtual void OnEnter(entt::registry& registry, float delta_time, entt::entity caster);
		virtual void OnUpdate(entt::registry& registry, float delta_time, entt::entity caster);
	protected:
		void GoNextState(entt::registry& registry, float delta_time, entt::entity caster);
		void SetupNewState(
			entt::registry& registry,
			entt::entity caster,
			AbilityState new_state,
			std::chrono::steady_clock::duration new_state_length = std::chrono::steady_clock::duration::min());
	};
}