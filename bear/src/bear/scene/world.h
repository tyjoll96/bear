#pragma once

#include <string>

#include <entt.hpp>

#include "bear/events/event.h"
#include "bear/imgui/imgui_system.h"

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
		float accumulator = 0.0f;
		ImGuiSystem* imgui_system_;
		std::vector<System*> systems_;
		entt::registry registry_;

		friend class EntityHandle;
	};
}