#pragma once

#include <cstdint>

#include "bear.h"

struct BasketballComponent
{
	uint8_t BallPosition = 2;
	uint8_t Player1Score = 0;
	uint8_t Player2Score = 0;
	bool Player1OnOffense = true;

	BasketballComponent() = default;
	// BasketballComponent(const BasketballComponent&) = default;
	BasketballComponent(bear::EntityHandle* offense_entity, bear::EntityHandle* defense_entity) {};

	void SetBallPosition(uint8_t ball_position)
	{
		if (ball_position > 4 || ball_position < 0) return;
		BallPosition = ball_position;
	}

	const static uint8_t DefaultBallPosition = 2;
};