#pragma once

#include <string>

#include <entt.hpp>

#include "bear/core/window.h"
#include "bear/events/application_event.h"
#include "bear/events/event.h"

#include "system.h"

namespace bear
{
	class EntityHandle;

	class World
	{
	public:
		World(const std::string& name = "something app");
		~World();

		void Run();

		void OnEvent(Event& e);

		void AddSystem(System* system);

		EntityHandle CreateEntity(const std::string& name = std::string());

		static World& Get();
		inline Window& GetWindow() { return *window_; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool running_ = true;
		float last_frame_time_ = 0.0f;
		std::unique_ptr<Window> window_;

		std::vector<System*> systems_;

		entt::registry registry_;

		friend class EntityHandle;
	};
}