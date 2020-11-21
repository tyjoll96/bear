#include "ability_state_check.h"

#include "../ability_caster_component.h"

void ralleon::AbilityStateCheck::OnUpdate(entt::registry& registry, float delta_time, entt::entity caster)
{
	std::cout << "Checking ability." << std::endl;
	auto ability_caster = &registry.get<AbilityCasterComponent>(caster);

	// check ability isn't on cooldown
	if (ability_caster->Cooldowns[ability_caster->CurrentAbilityIndex] > std::chrono::high_resolution_clock::now())
	{
		std::cout << "Ability on cooldown." << std::endl;
		ability_caster->State = AbilityState::kWait;
		return;
	}

	auto caster_transform = registry.get<bear::TransformComponent>(caster);
	auto target_transform = registry.get<bear::TransformComponent>(ability_caster->Target);

	// check target in range
	float distance_to_target = glm::distance(caster_transform.Transform[3], target_transform.Transform[3]);

	if (distance_to_target > range_)
	{
		std::cout << "You must get closer to your target." << std::endl;
		ability_caster->State = AbilityState::kWait;
		return;
	}

	// check target is in front of caster
	/*glm::vec3 from = caster_transform.Transform[3];
	glm::vec3 to = target_transform.Transform[3];
	to = to - from;

	glm::quat test = glm::quat_cast(caster_transform.Transform);
	glm::vec3 rot = test * glm::vec3(0.0f, 0.0f, 1.0f);
	from = glm::normalize(from);
	to = glm::normalize(to);

	float cosa = glm::clamp(glm::dot(from, to), -1.0f, 1.0f);
	std::cout << cosa << std::endl;

	glm::vec3 axis = glm::cross(from, to);
	float angle = glm::degrees(glm::acos(cosa));

	std::cout << angle << std::endl;
	std::cout << glm::radians(angle) << std::endl;

	ClearCurrentAbilityCast(&ability_caster);*/

	GoNextState(registry, delta_time, caster);
}
