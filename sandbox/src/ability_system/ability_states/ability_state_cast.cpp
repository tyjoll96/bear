#include "brpch.h"
#include "ability_state_cast.h"

#include "../ability.h"
#include "../castbar_component.h"

namespace ralleon
{
	AbilityStateCast::AbilityStateCast(std::chrono::steady_clock::duration state_duration)
		: state_duration_(state_duration)
	{
	}

	void AbilityStateCast::OnEnter(entt::registry& registry, float delta_time, entt::entity caster)
	{
		SetupNewState(registry, caster, AbilityState::kCast, state_duration_);
		std::cout << "Entering cast state." << std::endl;
		auto view = registry.view<CastbarComponent, bear::ImageComponent>();
		for (auto entity : view)
		{
			auto castbar = &registry.get<CastbarComponent>(entity);
			castbar->Duration = state_duration_;
			castbar->Reverse = false;
			castbar->StartTime = std::chrono::high_resolution_clock::now();

			auto image = &registry.get<bear::ImageComponent>(entity);
			image->Color = glm::vec4(0.8f, 0.8f, 0.1f, 1.0f);
		}
	}
}