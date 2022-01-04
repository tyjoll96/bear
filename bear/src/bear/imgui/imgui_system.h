#pragma once

#include "bear/scene/system.h"

namespace bear
{
	class ImGuiSystem : public bear::System
	{
	public:
		ImGuiSystem(const std::string& name = "ImGui system") : System(name) {}
		virtual ~ImGuiSystem() {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};
}