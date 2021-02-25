#pragma once

#include <string>

#include <entt.hpp>

#include "bear/events/event.h"

#include "system.h"

namespace bear
{
	class EntityHandle;

	class World
	{
	public:
		World();
		virtual ~World();

		void OnUpdate(float delta_time);
		void OnEvent(Event& e);

		void AddSystem(System* system);
		void PopulateFromJson(const std::string& j);
		EntityHandle CreateEntity(const std::string& name = std::string());

		static World& Get();
	private:
		std::vector<System*> systems_;

		entt::registry registry_;

		float accumulator = 0.0f;

		friend class EntityHandle;
	};
}