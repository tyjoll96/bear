#pragma once

#include <entt.hpp>

namespace ralleon
{
	struct CharacterComponent
	{
		float MissHealth = 0.0f;
		float MaxHealth = 100.0f;

		entt::entity Target = entt::null;

		CharacterComponent() = default;
		CharacterComponent(const CharacterComponent&) = default;
		CharacterComponent(float max_health)
			: MaxHealth(max_health) {}

		float CurrentHealth() const { return MaxHealth - MissHealth; }
	};
}