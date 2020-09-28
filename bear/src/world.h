#pragma once

#include <string>
#include <entt.hpp>

#include "window.h"
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

		void AddSystem(System* system);

		EntityHandle CreateEntity(const std::string& name = std::string());
	private:
		bool running_ = true;
		float last_frame_time_ = 0.0f;
		std::unique_ptr<Window> window_;

		std::vector<System*> systems_;

		entt::registry registry_;

		friend class EntityHandle;
	};
}