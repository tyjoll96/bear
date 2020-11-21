#pragma once

#include "bear.h"

namespace ralleon
{
	struct PlayerControllerComponent
	{
		float MoveSpeed;
		float RotationSpeed;

		PlayerControllerComponent() = default;
		PlayerControllerComponent(const PlayerControllerComponent&) = default;
		PlayerControllerComponent(float move_speed, float rotation_speed)
			: MoveSpeed(move_speed), RotationSpeed(rotation_speed) {}
	};

	class PlayerControllerSystem : public bear::System
	{
	public:
		PlayerControllerSystem(const std::string& name = "Player controller system") {}
		virtual ~PlayerControllerSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	};
}