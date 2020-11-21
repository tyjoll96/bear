#include "brpch.h"
#include "offense_system.h"

#include <glm/gtc/matrix_transform.hpp>

#include "bear/core/input.h"
#include "bear/core/key_codes.h"
#include "bear/events/event.h"
#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"

void SetSprite(bear::EntityHandle* sprite_handle, bgfx::TextureHandle texture)
{
	bear::SpriteComponent* sprite = &sprite_handle->GetComponent<bear::SpriteComponent>();

	if (!sprite) return;

	(*sprite).Th = texture;
}

OffenseSystem::OffenseSystem(BasketballComponent* basketball_component, bear::EntityHandle& sprite_entity, const std::string& name)
	: System(name), basketball_component_(basketball_component)
{
	idle_ = bear::BgfxUtils::LoadTexture("assets/textures/offense_idle.ktx");
	left_ = bear::BgfxUtils::LoadTexture("assets/textures/offense_left.ktx");
	right_ = bear::BgfxUtils::LoadTexture("assets/textures/offense_right.ktx");
	shoot_ = bear::BgfxUtils::LoadTexture("assets/textures/offense_shoot.ktx");

	sprite_entity.AddComponent<bear::SpriteComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), idle_);
	glm::mat4 player1mtx(1.0f);
	player1mtx = glm::scale(player1mtx, { 9.0f, 9.0f, 1.0f });
	sprite_entity.AddComponent<bear::TransformComponent>(player1mtx);
	sprite_handle_ = &sprite_entity;
}

OffenseSystem::~OffenseSystem()
{
	
}

void OffenseSystem::OnUpdate(entt::registry& registry, float delta_time)
{
	if (current_action_.IsActive)
	{
		if (std::chrono::steady_clock::now() <= current_action_.TimeOfCompletion) return;

		current_action_.IsActive = false;

		switch (current_action_.Direction)
		{
		case Direction::Left:
		case Direction::Right:
		{
			uint8_t change = 1 * basketball_component_->Player1OnOffense + -1 * !basketball_component_->Player1OnOffense;
			basketball_component_->SetBallPosition(basketball_component_->BallPosition + change);
			std::cout << unsigned(basketball_component_->BallPosition) << std::endl;
		}
		break;
		case Direction::Shoot:
		{
			if (basketball_component_->Player1OnOffense)
				basketball_component_->Player1Score++;
			else
				basketball_component_->Player2Score++;

			basketball_component_->Player1OnOffense = !basketball_component_->Player1OnOffense;
			basketball_component_->BallPosition = BasketballComponent::DefaultBallPosition;
		}
		break;
		}
	}

	if (bear::Input::IsKeyPressed(bear::Key::W))
		SetSprite(sprite_handle_, shoot_);
	else if (bear::Input::IsKeyPressed(bear::Key::A))
		SetSprite(sprite_handle_, left_);
	else if (bear::Input::IsKeyPressed(bear::Key::D))
		SetSprite(sprite_handle_, right_);
	else
		SetSprite(sprite_handle_, idle_);
}

void OffenseSystem::OnEvent(bear::Event& e)
{
	bear::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<bear::KeyPressedEvent>(BR_BIND_EVENT_FN(OffenseSystem::OnKeyPressedEvent));
}

bool OffenseSystem::OnKeyPressedEvent(bear::KeyPressedEvent& e)
{
	if (current_action_.IsActive) return false;
	if (basketball_component_->Player1OnOffense)
	{
		if (e.GetKeyCode() == bear::Key::C)
		{
			if (bear::Input::IsKeyPressed(bear::Key::W))
			{
				current_action_ = { true, Direction::Shoot, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, shoot_);
			}
			else if (bear::Input::IsKeyPressed(bear::Key::A))
			{
				current_action_ = { true, Direction::Left, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, left_);
			}
			else if (bear::Input::IsKeyPressed(bear::Key::D))
			{
				current_action_ = { true, Direction::Right, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, right_);
			}
		}
	}
	else
	{
		if (e.GetKeyCode() == bear::Key::N)
		{
			if (bear::Input::IsKeyPressed(bear::Key::T))
			{
				current_action_ = { true, Direction::Shoot, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, shoot_);
				basketball_component_->Player1Score++;
				std::cout << unsigned(basketball_component_->Player1Score) << std::endl;
			}
			else if (bear::Input::IsKeyPressed(bear::Key::F))
			{
				current_action_ = { true, Direction::Left, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, left_);
			}
			else if (bear::Input::IsKeyPressed(bear::Key::H))
			{
				current_action_ = { true, Direction::Right, std::chrono::high_resolution_clock::now() + std::chrono::seconds(5) };
				SetSprite(sprite_handle_, right_);
			}
		}
	}
	return false;
}
