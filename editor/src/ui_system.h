#pragma once

#include "bear/scene/system.h"

namespace editor
{
	class UiSystem : public bear::System
	{
	public:
		UiSystem(const std::string& name = "Targetting system") : System(name) {}
		virtual ~UiSystem() {}

		virtual void OnAttach() override;
		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
		virtual void OnImGuiUpdate() override;
	};
}