#pragma once

#include <entt.hpp>
#include <string>

#include "bear/events/event.h"

namespace bear
{
	class System
	{
	public:
		System(const std::string& name = "System") : debug_name_(name) {}
		virtual ~System() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(entt::registry& registry, float delta_time) {}
		virtual void OnEvent(Event& e) {}
	protected:
		std::string debug_name_;
	};
}