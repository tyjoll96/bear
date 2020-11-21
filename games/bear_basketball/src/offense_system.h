#pragma once

#include "bear/scene/system.h"

#include <chrono>

#include <bgfx/bgfx.h>

#include "bear/scene/entity_handle.h"
#include "bear/renderer/rendering_2d_system/sprite_component.h"
#include "bear/events/key_event.h"

#include "basketball_components.h"

class OffenseSystem : public bear::System
{
public:
	OffenseSystem(BasketballComponent* basketball_component, bear::EntityHandle& sprite_handle, const std::string& name = "Attacker system");
	virtual ~OffenseSystem();

	virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	virtual void OnEvent(bear::Event& e) override;
	bool OnKeyPressedEvent(bear::KeyPressedEvent& e);
private:
	enum Direction {
		Left,
		Right,
		Shoot
	};

	struct OffenseAction {
		bool IsActive;
		Direction Direction;
		std::chrono::steady_clock::time_point TimeOfCompletion;
	};

	bgfx::TextureHandle idle_, right_, left_, shoot_;
	BasketballComponent* basketball_component_;
	bear::EntityHandle* sprite_handle_;
	OffenseAction current_action_ = { false, Direction::Left, std::chrono::high_resolution_clock::time_point::min() };
};